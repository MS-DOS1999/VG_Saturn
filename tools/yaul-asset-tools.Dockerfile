FROM ijacquez/yaul:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update --allow-releaseinfo-change \
    && apt-get install -y --no-install-recommends \
        imagemagick \
        pngquant \
        python3 \
        python3-pil \
    && rm -rf /var/lib/apt/lists/*
