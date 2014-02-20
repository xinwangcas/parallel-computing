/**
 *  origin:  lehigh cse department
 *  course:  cse 375/475
 *  date:    2013-09-11
 *  version: 1
 *
 *  description: this file implements the ocean simulations
 *
 *  this should be the focal point for student efforts to implement their
 *  programs.
 */

#include <iostream>

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "config_t.hpp"
#include "ocean.hpp"

using std::cout;
using std::endl;
using namespace tbb;

/**
 *  an array of points, to simulate our ocean
 */
float* ocean_points;
/**
 *  allocate an ocean and populate it with random floats.  since this is an
 *  ocean simulation, we'll use reasonable celsius temperatures (e.g.,
 *  between 0 and 51), and we'll only have 3 significant digits to the right
 *  of the decimal.
 */
void init_ocean(config_t& cfg)
{
	// make a copy of the seed, since it gets modified by each call to
	// rand_r()
	unsigned seed = cfg.seed;

	ocean_points = new float[cfg.gridsize * cfg.gridsize];
	for (int i = 0; i < cfg.gridsize * cfg.gridsize; ++i) {
		// nb: making a random float from two random ints that we mod into a
		// reasonable range
		unsigned lhs = rand_r(&seed);
		unsigned rhs = rand_r(&seed);
		lhs = lhs % 50;
		rhs = rhs % 1000;
		float value = rhs;
		value = value / (float)1000;
		value += lhs;
		ocean_points[i] = value;
	}
}

/**
 *  when a simulation is done, we can use this to free the ocean_points data
 *  structure.
 */
void free_ocean(config_t& cfg)
{
	free(ocean_points);
}

/**
 *  simple print routine to show the state of the ocean_points array
 */
void dump_ocean(config_t& cfg)
{
	if (!cfg.verbose)
		return;
	for (int i = 0; i < cfg.gridsize * cfg.gridsize; ++i) {
		cout << ocean_points[i];
		if ((i + 1) % cfg.gridsize == 0)
			cout << endl;
		else
			cout << ", ";
	}
}


void swap(float* &a, float* &b){
	float *t;
	t = a;
	a = b;
	b = t;
}
/**
 *  perform a sequential ocean simulation
 */

void ocean_sequential(config_t& cfg)
{
	// todo: simulate ocean for appropriate number of timesteps

	float *temp = new float[cfg.gridsize*cfg.gridsize];
	for (int n = 0 ; n < cfg.iters ; n ++){
		for (int i = 0 ; i < cfg.gridsize * cfg.gridsize ; i ++){
			if(i/cfg.gridsize == 0 || i/cfg.gridsize == cfg.gridsize-1 || i%cfg.gridsize == 0 || i%cfg.gridsize == cfg.gridsize-1){
				temp[i] = ocean_points[i];
			}
			else{
				temp[i] = (ocean_points[(i/cfg.gridsize-1)*cfg.gridsize + i%cfg.gridsize]+ocean_points[(i/cfg.gridsize+1)*cfg.gridsize+i%cfg.gridsize]+ocean_points[i-1]+ocean_points[i]+ocean_points[i+1])/5;
			}
		}
		swap(ocean_points,temp);
	}
}

/**
 *  Perform a parallel ocean simulation, using TBB
 */

class parallel{
public:
	float** input;
	float** output;
	int size;
	
	parallel(float* &inp, float* &outp, int n):input(&inp),output(&outp),size(n){};
	void operator()(const blocked_range<int>& range) const{
		for(int i = range.begin(); i != range.end(); i++){
			if(i/size == 0 || i/size == size-1 || i%size == 0 || i%size == size-1){
				(*output)[i] = (*input)[i];
			}
			else{
				(*output)[i] = ((*input)[(i/size-1)*size+i%size]+(*input)[(i/size+1)*size+i%size]+(*input)[i-1]+(*input)[i]+(*input)[i+1])/5;
			}
		}
	}
};

void ocean_parallel(config_t& cfg){
	float* output = new float[cfg.gridsize*cfg.gridsize];
	parallel pa(ocean_points, output, cfg.gridsize);
	
	for(int i = 0; i < cfg.iters ; i++){
		parallel_for(blocked_range<int>(0, cfg.gridsize*cfg.gridsize, cfg.gridsize/2), pa);
		swap(ocean_points, output);
	}

	free(output);
}

