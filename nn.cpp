#include <iostream>
#include <map>
#include <vector>

struct Neuron{
  std::map<float, float> input_weight_vector;
};

struct Layer{
  std::vector<Neuron> neurons;	
};

class NN{
 Layer input;
 Layer output;
 std::vector<Layer> hidden;

 public:
   NN(std::vector<float> inputs, std::vector<float> outputs){
     std::map<float, float> input_weight_vector;
     for(const auto& elt: inputs ){
       	input_weight_vector.insert({elt, elt/2});     
     }
     Neuron input_neuron{input_weight_vector};
   }
};
