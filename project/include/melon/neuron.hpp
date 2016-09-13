#ifndef _PERCEPTRON_H_
#define _PERCEPTRON_H_
#include <melon/vec.hpp>
#include <melon/mat.hpp>
#include <string>
#include <zoson/object.hpp>
using namespace std;

namespace melon
{

class Neuron:virtual public zoson::Object
{
public:
	Neuron()
	{
		m_out_data = new Vector<double>();
	}
	virtual ~Neuron()
	{
		delete m_out_data;
	}
	virtual Vector<double>* forward(Matrix<double> *data)=0;
	virtual Vector<double>* backward(Vector<double> *label)=0;
	virtual double test(Vector<double>* test)=0;
	virtual void updateWeight()=0;
	virtual inline string getType(){return "Neuron"; }
	virtual string print()=0;
	virtual inline string toString(){return "Neuron";};
protected:
	Vector<double>* m_out_data; // store out_data
	Matrix<double>* m_in_data; //store in_data
};

}

#endif