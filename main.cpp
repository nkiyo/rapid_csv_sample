#include <vector>
#include <string>
#include <stdio.h>
#include "rapidcsv.h"

using std::string;
using std::vector;

int main() {
  rapidcsv::Document doc("csv/sample.csv", rapidcsv::LabelParams(0, 0));

  // 列単位で取り出す(int) => row header となる列はGetColumnでは取得できない
  //vector<int> col1 = doc.GetColumn<int>("ID");
  //for (auto cell: col1)
  //  printf("%d ", cell);
  //printf("\n");

  // 列単位で取り出す(double)
  vector<double> col2 = doc.GetColumn<double>("Float");
  for (auto cell: col2)
    printf("%f ", cell);
  printf("\n");

  // 列単位で取り出す(string)
  vector<string> col3 = doc.GetColumn<string>("Message");
  for (auto cell: col3)
    printf("[%s] ", cell.c_str());
  printf("\n");

  // セル単位で取り出す(double)
  // row headerは、文字列形式で渡す
  double d = doc.GetCell<double>("Float", "10");
  printf("%f\n", d);

  // 無効なカラム名を指定した場合
  //double cell2 = doc.GetCell<double>("NonExistentColumn", "10");
  // => std::out_of_range

  // 無効なrow headerを指定した場合
  //double cell3 = doc.GetCell<double>("Float", "12345");
  // => std::out_of_range
  
  // TODO 期待するデータ型を取得した場合 
  // 可能な限り、キャストする
  // 以下のような string => int のような無茶なキャストの場合・・・？
  int cell4 = doc.GetCell<int>("Message", "10");
  printf("[%d]\n", cell4);
}
