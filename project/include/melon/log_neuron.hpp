#ifndef _LOGREGRES_H_
#define _LOGREGRES_H_
#include <melon/neuron.hpp>
#include <vector>
#include <melon/vec.hpp>
#include <melon/mat.hpp>
#include <ostream>
using namespace std;
namespace melon
{

class LogNeuron:public Neuron
{
public:
	LogNeuron(){}
	~LogNeuron(){}
	virtual void initSpec(int in_dim); 	
	virtual Vector<double> forward(Matrix<double> &data);
	virtual double forward(Vector<double> &);
	virtual Vector<double> backward(Vector<double> &label);
	virtual double backward(double label);
	virtual void updateWeight();
	virtual void print(ostream &out);
};

}

#endif