#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

#define TABLE_LENGHT 4
#define TABLE_WIDTH 3
#define FILE_NAME "TruthTable.txt"
#define DEBUG_TRAINING 0
#define THRESHOLD 0.9

using namespace std;

class Perceptron {
public:
    Perceptron(double tr, double lr, double p1, double p2) : threshold(tr), learningRate(lr) {
        this->weights.push_back(p1);
        this->weights.push_back(p2);
    }
    void TrainPerceptron(const vector< vector<int> >& trainingData);
    int run(double x, double y);
private:
    double threshold;
    double learningRate;
    double output;
    vector<double> weights;
};

//Functions definitions
void ReadDataSet(vector< vector<int> > &data);
void ShowDataSet(const vector< vector<int> > &data);
void Presentation();

int main(){
    double random_weight1, random_weight2, x, y;
    int z;

    vector< vector<int> > data_set(TABLE_LENGHT);
    for(int i = 0; i < data_set.size(); ++i){
        data_set[i].resize(TABLE_WIDTH);
    }

    Presentation();
    try{
        ReadDataSet(data_set);
    }catch(const char* msg){
        cout << msg << endl;
    }
    ShowDataSet(data_set);

    srand(time(0));
    random_weight1 = (double)(rand()%41 - 20)/10;
    random_weight2 = (double)(rand()%41 - 20)/10;    

    Perceptron mlp(THRESHOLD, 0.1, random_weight1, random_weight2);
    mlp.TrainPerceptron(data_set);

    cout << "Now you can test it!!!(-1 to stop)" << endl;
    while(true){
        cout << "Entrada 1: ";
        cin >> x;
        if(x == -1) break;
        cout << "Entrada 2: ";
        cin >> y;

        z = mlp.run(x, y);
        cout << "Saida: " << z << endl;
    }
    return 0;
}

//------------------ Global functions implementations  ------------------
void Presentation(){
    cout << "---------------------------------------------------- Perceptron ----------------------------------------------------" << endl;
    cout << "This program was made to simulade GATE PORTS(AND, OR...) \nwith the simplest neural network(Perceptron)\n";
    cout << "there is only an input layer with 2 neurons and one output layer with one neuron, it will output 1 or 0.\n";
    cout << "You will have to input the truth table throught the file TruthTable.txt and it will train to output the correct values\n";
    cout << "--------------------------------------------------------------------------------------------------------------------\n" << endl;
}

void ReadDataSet(vector< vector<int> > &data){
    ifstream table(FILE_NAME);
    if(table.is_open()){
        for(int i = 0; i < TABLE_LENGHT; ++i){
            table >> data[i][0] >> data[i][1] >> data[i][2];
        }
    }
    else{
        throw "Cannot Read Truth Table";
    }
}

void ShowDataSet(const vector< vector<int> > &data){
    cout << endl << "INPUT TABLE: " << endl;
    cout << "\tX\tY\t  Z" << endl;
    cout << "\t---------------------" << endl;
    for(int i = 0 ; i < TABLE_LENGHT; ++i){
        for(int j = 0; j < TABLE_WIDTH; ++j){
            if(j == TABLE_WIDTH-1){
                cout << "| ";
            }
            if(j == 0){
                cout << "\t";
            } 
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}
//------------------------------------------------------------------------

//------------------ Perceptron functions implementations  ------------------
void Perceptron::TrainPerceptron(const vector< vector<int> >& trainingData){
    cout << endl << "TRAINING..." << endl;
    int c = 1;
    double input_x, input_y, sum;
    int output, error;
    char pause;
    while(true){ 
        c = 0;
        for(int i = 0; i < TABLE_LENGHT; ++i){
            //calcule error
            input_x = trainingData[i][0] * this->weights[0];
            input_y = trainingData[i][1] * this->weights[1];
            sum = input_x + input_y;
            if(sum > this->threshold){
                output = 1;
            }
            else{
                output = 0;
            }
            if(DEBUG_TRAINING){
                cout << "Caso " << i << endl;
                cout << "pesos: " << this->weights[0] << " , " << this->weights[1] << endl;
                cout << "input_x: " << input_x << endl;
                cout << "input_y: " << input_y << endl;
                cout << "output: " << output << endl;
            }
            if(output != trainingData[i][2]){
                c = 1;
                error = trainingData[i][2] - output;
                this->weights[0] = this->weights[0] + (error * trainingData[i][0] * this->learningRate);
                this->weights[1] = this->weights[1] + (error * trainingData[i][1] * this->learningRate); 
                if(DEBUG_TRAINING){
                    cout << "Error: " << error << endl;
                    cout << "novos pesos: " << this->weights[0] << " , " << this->weights[1] << endl;
                }
            }
        }
        if(c == 0) break;
    }

    cout << endl << "Final weights: " << this->weights[0] << " , " << this->weights[1] << endl;
}

int Perceptron::run(double x, double y){
    double input_x = x * this->weights[0];
    double input_y = y * this->weights[1];
    double sum = input_x + input_y;

    if(sum > this->threshold){
        return 1;
    }
    return 0;
}
//---------------------------------------------------------------------------