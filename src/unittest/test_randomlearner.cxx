#include <vector>

#include <opengm/functions/explicit_function.hxx>
#include <opengm/unittests/test.hxx>
#include <opengm/graphicalmodel/graphicalmodel.hxx>
#include <opengm/operations/adder.hxx>
#include <opengm/operations/minimizer.hxx>
#include <opengm/inference/icm.hxx>
#include <opengm/utilities/metaprogramming.hxx>

#include <opengm/functions/learnable/lpotts.hxx>
#include <opengm/learning/randomlearner.hxx>
#include <opengm/learning/loss/hammingloss.hxx>
#include <opengm/learning/dataset/testdataset.hxx>


//*************************************
typedef double ValueType;
typedef size_t IndexType;
typedef size_t LabelType; 
typedef opengm::meta::TypeListGenerator<opengm::ExplicitFunction<ValueType,IndexType,LabelType>, opengm::functions::learnable::LPotts<ValueType,IndexType,LabelType> >::type FunctionListType;
typedef opengm::GraphicalModel<ValueType,opengm::Adder, FunctionListType, opengm::DiscreteSpace<IndexType,LabelType> > GM; 
typedef opengm::datasets::TestDataset<GM> DS;
typedef opengm::learning::HammingLoss     LOSS;
typedef opengm::ICM<GM,opengm::Minimizer> INF;

//*************************************


int main() {
   std::cout << " Includes are fine :-) " << std::endl; 
  
   DS dataset;
   std::cout << "Dataset includes " << dataset.getNumberOfModels() << " instances and has " << dataset.getNumberOfParameters() << " parameters."<<std::endl; 
  

   opengm::learning::GridSearchLearner<DS,LOSS>::Parameter para;
   para.parameterUpperbound_.resize(1,1);
   para.parameterLowerbound_.resize(1,0);
   para.testingPoints_.resize(1,10);
   opengm::learning::GridSearchLearner<DS,LOSS> learner(dataset,para);


   INF::Parameter infPara;
   learner.learn<INF>(infPara);

}
