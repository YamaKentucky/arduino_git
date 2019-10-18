#include <Eigen.h>     // Calls main Eigen matrix class library
#include <Eigen/LU>             // Calls inverse, determinant, LU decomp., etc.
using namespace Eigen;    // Eigen related statement; simplifies syntax for declaration of matrices
Matrix3d M, N, A, B, C;



void setup() {
  Serial.begin(9600);
  M << 1, 2, 3,
  4, 5, 6,
  7, 8, 9;
  N << 1, 2, 3,
  4, 5, 6,
  7, 8, 9;
  A = M + N;
  B = M - N;
  C = M * N;
}




void loop() {


  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.println(A(i, j));
      delay(1000);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.println(B(i, j));
      delay(1000);
    }
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Serial.println(C(i, j));
      delay(1000);
    }
  }

}





