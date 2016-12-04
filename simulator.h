#ifndef SIMULATOR_H_
#define SIMULATOR_H_

void process();

void init(int psize, int winsize);

void put (unsigned int address, int value);

int get(unsigned int address);

void done();

#endif // SIMULATOR_H_
