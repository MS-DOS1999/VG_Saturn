all: main.elf

include $(KOS_BASE)/Makefile.rules

SRC = ../../source/cpp/Font.cpp ../../source/cpp/stdafx.cpp ../../source/dc/Super_trench_attack-STEAM_DC.cpp ../../source/dc/interface.cpp ../../source/dc/ram_tracking.cpp ../../source/dc/joypad.cpp

OBJS := $(filter %.o,$(SRC:.cpp=.o))

CFLAGS += -O2 -Wno-format-zero-length -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-variable -Wno-unused-but-set-variable -Wno-write-strings -Wno-reorder -Wno-sign-compare -D DREAMCAST -I$(KOS_BASE)/addons/zlib -I../../source/h -I../../source/dc/GLdc -I../../source/dc

ROMDISKS_LIST = bg_airport.img bg_alleyway.img bg_bikeshop.img bg_bonus.img bg_cafe.img bg_court.img bg_dojo.img bg_highway.img bg_nightclub.img bg_park.img bg_prison.img bg_ring.img bg_rooftops.img bg_traffic.img bg_train.img cs_bossidle.img cs_danger1.img cs_danger2.img cs_ending.img cs_idle.img cs_intro.img cs_victory.img vg_amb_car1.img vg_amb_car2.img vg_amb_duel.img vg_amb_prison.img vg_amb_subway.img vg_amb_traffic.img vg_gameover.img vg_select.img vg_van.img vg_vs.img

clean:
	-rm -f main.elf $(OBJS)
	-rm -f *.cdi
	-rm -f main.bin
	-rm -f 1ST_READ.BIN
	-rm -f romdisk.img
dist:
	-rm -f $(OBJS)
	$(KOS_STRIP) main.elf
	
rm-elf:
	-rm -f main.elf

main.elf: $(OBJS)
	-rm -f 1ST_READ.BIN
	-rm -f main.bin
	-rm -f main.elf
	kos-c++ -o $@ $(KOS_START) $^ -lm -lkosutils -L./libvfdc/lib -lkmg -L./../../source/dc -lGLdc -lADX $(KOS_LIBS)
	
	
# Cible pour générer tous les romdisks
all_romdisk: $(ROMDISKS_LIST)

# Règle pour chaque romdisk
$(ROMDISKS_LIST):
	$(KOS_GENROMFS) -f $@ -d BGM/$(basename $@) -v
	mv $@ ../../data/dc/data/$@
	
clean_romdisk:
	-rm -f *.img

cdi:
	../../Tools/mkdcdisc/builddir/mkdcdisc -v 3 -a PIXELHEART -d ../../data/dc/data -d ../../data/dc/scene -f ../../data/dc/bg_airport.img -f ../../data/dc/bg_alleyway.img -f ../../data/dc/bg_bikeshop.img -f ../../data/dc/bg_bonus.img -f ../../data/dc/bg_cafe.img -f ../../data/dc/bg_court.img -f ../../data/dc/bg_dojo.img -f ../../data/dc/bg_highway.img -f ../../data/dc/bg_nightclub.img -f ../../data/dc/bg_park.img -f ../../data/dc/bg_prison.img -f ../../data/dc/bg_ring.img -f ../../data/dc/bg_rooftops.img -f ../../data/dc/bg_traffic.img -f ../../data/dc/bg_train.img -f ../../data/dc/cs_bossidle.img -f ../../data/dc/cs_danger1.img -f ../../data/dc/cs_danger2.img -f ../../data/dc/cs_ending.img -f ../../data/dc/cs_idle.img -f ../../data/dc/cs_intro.img -f ../../data/dc/cs_victory.img -f ../../data/dc/vg_amb_car1.img -f ../../data/dc/vg_amb_car2.img -f ../../data/dc/vg_amb_duel.img -f ../../data/dc/vg_amb_prison.img -f ../../data/dc/vg_amb_subway.img -f ../../data/dc/vg_amb_traffic.img -f ../../data/dc/vg_gameover.img -f ../../data/dc/vg_select.img -f ../../data/dc/vg_van.img -f ../../data/dc/vg_vs.img -e main.elf -N -n VERDICT_____ -o Verdict_Dev.cdi
	

execute:
	mkisofs -l -o data.iso ./preparetoCDI
	sudo /opt/toolchains/dc/bin/dc-tool-ser -x main.elf -i data.iso -b 1500000 -t /dev/ttyS3


