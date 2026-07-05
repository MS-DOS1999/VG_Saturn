FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        curl \
        libasound2-dev \
        libflac-dev \
        libsdl2-dev \
        pkg-config \
        python3 \
        xz-utils \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/mednafen-build

RUN curl -L https://mednafen.github.io/releases/files/mednafen-1.32.1.tar.xz -o mednafen-1.32.1.tar.xz \
    && tar -xf mednafen-1.32.1.tar.xz

WORKDIR /tmp/mednafen-build/mednafen

RUN python3 - <<'PY'
from pathlib import Path

p = Path("src/ss/cart.cpp")
s = p.read_text()
s = s.replace(
    "#include <mednafen/general.h>\n",
    "#include <mednafen/general.h>\n#include <stdio.h>\n",
)
old = """template<typename T>
static MDFN_HOT void DummyWrite(uint32 A, uint16* DB)
{
 SS_DBG(SS_DBG_WARNING, "[CART] Unknown %zu-byte write to 0x%08x(DB=0x%04x)\\n", sizeof(T), A, *DB);
}
"""
new = """template<typename T>
static MDFN_HOT void DummyWrite(uint32 A, uint16* DB)
{
 if(sizeof(T) == 1 && A == 0x02100001)
 {
  const uint8 v = (uint8)(*DB & 0xFF);

  if(v != 0x00 && v != 0x1B)
  {
   fputc(v, stdout);
   fflush(stdout);
  }

  return;
 }

 SS_DBG(SS_DBG_WARNING, "[CART] Unknown %zu-byte write to 0x%08x(DB=0x%04x)\\n", sizeof(T), A, *DB);
}
"""
if old not in s:
    raise SystemExit("cart.cpp DummyWrite pattern not found")
p.write_text(s.replace(old, new))
PY

RUN ./configure --enable-dev-build --prefix=/opt/mednafen-ss-dev \
    && make -j2 \
    && make install

ENTRYPOINT ["/opt/mednafen-ss-dev/bin/mednafen"]
