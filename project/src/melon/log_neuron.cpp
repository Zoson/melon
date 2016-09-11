#include <melon/log_neuron.hpp>
#include <iostream>
#include <ostream>
#include <melon/vec.hpp>
#include <utils/func.hpp>
using namespace std;
namespace melon
{

double LogNeuron::forward(Vector<double> &data)
{
	if(data.getDim()!=m_weight.getDim())
	{
		throw "dim no same";
	}else{
		m_out_data.clear();
		m_in_data.clear();
		m_in_data.push(data);
		double dot = data * m_weight;
		dot = sigmod<double>(dot);
		m_out_data.push(dot);
		return dot;
	}
}

Vector<double> LogNeuron::forward(Matrix<double> &data)
{
	if(data.getCol()!=m_weight.getDim()){
		throw "dim no same";
	}else{
		m_out_data.clear();
		m_out_data = data*m_weight;
		m_in_data.clear();
		m_in_data = data;
		sigmod<double>(m_out_data);
		return m_out_data;
	}
}

Vector<double> LogNeuron::backward(Vector<double>& label)
{
	m_loss.clear();
	m_loss = m_out_data - label;
	return m_loss;
}

double LogNeuron::backward(double label)
{
	m_loss.clear();
	double diff = m_out_data[0] - label;
	m_loss.push(diff);
	return diff;
}

void LogNeuron::updateWeight()
{
	if(m_loss.getDim()<0)return;
	int row = m_in_data.getRow();
	m_weight = m_weight - ((m_in_data.transpose()*m_loss)*m_lr)/row;
}


void LogNeuron::initSpec(int in_dim)
{
	for(int i=0;i<in_dim;++i)
	{
		m_weight.push(1.0);
	}
}

void LogNeuron::print(ostream &out)
{
	for(int i=0;i<m_weight.getDim();++i)
	{
		out<<m_weight[i]<<" ";
	}
	out<<endl;
}


}
