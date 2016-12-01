CXX=mpic++ -Wall -O3


CPPFLAGS=-Iinc

LDFLAGS=-lboost_program_options -lm

FILES=export forward init memory parse_args shalw share_lines
OBJECTS=$(addsuffix .o, $(FILES))
BIN=bin/shalw

all : $(BIN)

$(BIN) : $(addprefix obj/, $(OBJECTS))
	$(CXX) -o $@ $^ $(LDFLAGS)

obj/%.o : src/%.cpp
	$(CXX) -c -o $@ $^ $(CPPFLAGS)

obj/%.o : src/%.c
	$(CXX) -c -o $@ $^ $(CPPFLAGS)

clean :
	rm -f bin/* obj/*

exec :
	mpirun -hostfile hostfile -np 2 bin/shalw -x 8192 -y 8192 -t 20

show :
	./visu.py /tmp/3502158/shalw_256x256_T1000.sav 
