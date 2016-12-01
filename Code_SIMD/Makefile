CXX=mpic++ -Wall -O3


CPPFLAGS=-Iinc -fopenmp -msse3 -ffast-math -mavx2 -mfma

LDFLAGS=-lboost_program_options -lm -fopenmp -msse3 -ffast-math -mavx2 -mfma

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
	mpirun -hostfile hostfile -np 16 bin/shalw -x 16132 -y 16132 -t 50

show :
	./visu.py /tmp/3502158/shalw_256x256_T1000.sav 
