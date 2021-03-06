#include <melon/softmax_neuron.hpp>
#include <sstream>
#include <float.h>
#include <iostream>
#include <utils/func.hpp>
using namespace std;
namespace melon
{

Matrix<double>* SoftMaxNeuron::forward(Matrix<double>*data)
{
	if(data==NULL)return NULL;
	if(data->getCol()!=m_weight.getCol())
	{
		cout<<"dim no same"<<endl;
	}
	m_in_data = data;
	m_out_data->clear();
	int m = data->getRow();
	int row = m_weight.getRow();
	for(int i=0;i<m;++i)
	{
		Vector<double>* vec = new Vector<double>();
		m_out_data->insertRow(*vec);
		for(int j=0;j<row;++j)
		{
			double p = softmax(&(*data)[i],j);
			(*m_out_data)[i].push(p);
		}
	}
	return m_out_data;
}

Matrix<double>* SoftMaxNeuron::forward(Matrix<double>*data,Matrix<double>*data_t)
{
	m_in_data = data;
	m_in_data_t = data_t;
	return forward(data);
}

double SoftMaxNeuron::softmax(Vector<double>* x,int n)
{
	double den = 0;//分母
	int k = m_weight.getRow();
	double mol = (m_weight[n]*(*x));
	for(int i=0;i<k;++i)
	{
		den += exp(m_weight[i]*(*x)-mol);
	}
	double res = 1/den;
	return res;
}

Matrix<double>* SoftMaxNeuron::backward(Vector<double>*label)
{
	if(label==NULL)return NULL;
	m_loss->clear();
	int row = label->getDim();
	int k = m_weight.getRow();
	for(int i=0;i<row;++i)
	{
		m_loss->insertRow(*(new Vector<double>()));
		for(int j=0;j<k;++j)
		{		
			double loss = 0;
			int l = (*label)[i]>0?1:0;
			if(l==j)loss+=1;
			loss += - (*m_out_data)[i][j];
			(*m_loss)[i].push(loss);
		}
	}
	return m_loss;
}

void SoftMaxNeuron::updateWeight()
{
	int k = m_weight.getRow();
	int row = m_in_data->getRow();
	double alpha = m_lr/row;
	//cout<<alpha<<endl;
	Matrix<double> grad = ((*m_in_data_t)*(*m_loss))*alpha;
	//cout<<grad.print();
	m_weight = m_weight + grad.transpose();//+ grad;
}

void SoftMaxNeuron::initSpec(int r,int c,double val)
{
	for(int i=0;i<r;++i)
	{
		m_weight.insertRow(*(new Vector<double>()));
		for(int j=0;j<c;++j)
		{
			m_weight[i].push(val);
		}
	}
}

double SoftMaxNeuron::test(Vector<double> *x)
{
	int min_index = 0;
	double min_val = DBL_MIN;
	int k = m_weight.getRow();
	double out = 0;
	for(int i=0;i<k;++i)
	{
		double mol = m_weight[i]*(*x);
		double den =0;
		for(int i=0;i<k;++i)
		{
			den += exp(m_weight[i]*(*x)-mol);
		}
		out = 1/den;
		if(out>min_val)
		{
			min_val = out;
			min_index = i;
		}
	}
	return min_index;
}

string SoftMaxNeuron::print()
{
	stringstream ss;
	int row = m_weight.getRow();
	int col = m_weight.getCol();
	for(int i=0;i<row;++i)
	{
		for(int j=0;j<col;++j)
		{
			ss<<m_weight[i][j]<<" ";
		}
		ss<<"\r\n";
	}
	ss<<"\r\n";
	return ss.str();
}


}