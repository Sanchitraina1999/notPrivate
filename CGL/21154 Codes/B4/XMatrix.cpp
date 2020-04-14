#include"iostream"
using namespace std;

class XMatrix{
private:
    float **matrix;
    int n;
public:
    XMatrix(int);
    XMatrix operator *(XMatrix&);
    void printOnTerminal();
    friend class MainWindow;
};
XMatrix::XMatrix(int n){
    this->n=n;
    matrix=new float* [n];
    for(int i=0;i<n;i++)
        matrix[i]=new float[3];

    for(int i=0;i<n;i++)
        for(int j=0;j<3;j++)
            matrix[i][j]=1;

}
XMatrix XMatrix::operator *(XMatrix &obj2){
    XMatrix result(this->n);
    for(int i=0;i<this->n;i++){
        for(int j=0;j<3;j++){
            result.matrix[i][j]=0;
            for(int k=0;k<3;k++){
                result.matrix[i][j]+=this->matrix[i][k]*obj2.matrix[k][j];
            }
        }
    }
    return result;
}
void XMatrix::printOnTerminal(){
    cout<<"\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            cout<<matrix[i][j]<<"\t";
        }
        cout<<"\n\n\n";
    }
}
