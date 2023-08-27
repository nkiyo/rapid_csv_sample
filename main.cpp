#include <vector>
#include <string>
#include <stdio.h>
#include "rapidcsv.h"

using std::string;
using std::vector;

int main() {
  // 1列目(ID)を row header として、csvを読む
  rapidcsv::Document doc("csv/sample.csv", rapidcsv::LabelParams(0, 0));

  // 列単位で取り出す(int) => row header となる列はGetColumnでは取得できないので注意
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

  try {
    // 無効なカラム名を指定した場合
    //double cell2 = doc.GetCell<double>("NonExistentColumn", "10");
    // => std::out_of_range

    // 無効なrow headerを指定した場合
    // double cell3 = doc.GetCell<double>("Float", "12345");
    // => std::out_of_range
    
    // 期待と異なるデータ型を取得した場合 
    // 可能な限り、キャストするらしいが、
    // 以下のような string => int のような無茶なキャストの場合
    // int cell4 = doc.GetCell<int>("Message", "10");
    // => std::invalid_argument
  } catch(std::out_of_range& e) {
    printf("out_of_range catched.\n");
    printf("%s\n", e.what());
  } catch(std::invalid_argument& e) {
    printf("invalid_argument catched.\n");
    printf("%s\n", e.what());
  } catch(std::exception& e) {
    // 単なるthrowだとここに来る
    printf("unexpected exception catched.\n");
    printf("%s\n", e.what());
  } catch(...) {
    // ここは通らない
    printf("unexpected exception catched. (2)\n");
  }
}
