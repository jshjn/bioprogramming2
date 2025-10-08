#include<iostream>
#include<string>
using namespace std;

int main(void){
   string s="123";

   s=s+"aaa"; //直観的に数式以外もかける
   s+='b';
   cout<<s<<endl;

   if(s=="123aaab"){
    cout<<"equal!"<<endl;
   }

   return 0;
}