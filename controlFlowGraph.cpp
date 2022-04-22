#include <fstream>
#include <bits/stdc++.h>
using namespace std;

int searchIf(vector<pair<int, int>> &ifStatement, int v)
{
   v++;
   for (int i = 0; i < ifStatement.size(); i++)
   {
      if (ifStatement[i].first == v)
      {
         return ifStatement[i].second;
      }
   }
   return -1;
}

int searchElseif(vector<pair<int, int>> &elseifStatement, pair<int, int> &v)
{
   int l = 0, r = elseifStatement.size() - 1;
   while (l <= r)
   {
      int mid = (l + r) / 2;
      if (elseifStatement[mid].first == v.second + 2)
      {
         return v.second + 1;
      }
      else if (elseifStatement[mid].first > v.second + 2)
      {
         r = mid - 1;
      }
      else
      {
         l = mid + 1;
      }
   }
   return -1;
}

int searchElse(vector<pair<int, int>> &elseStatement, pair<int, int> &v)
{
   int l = 0, r = elseStatement.size() - 1;
   while (l <= r)
   {
      int mid = (l + r) / 2;
      if (elseStatement[mid].first == v.second + 2)
      {
         return v.second + 1;
      }
      else if (elseStatement[mid].first > v.second + 2)
      {
         r = mid - 1;
      }
      else
      {
         l = mid + 1;
      }
   }
   return -1;
}

int main()
{
   fstream newfile;
   newfile.open("input.txt", ios::in); // open a file to perform read operation using file object
   if (newfile.is_open())
   { // checking whether the file is open
      string tp;
      int line = 1;
      vector<vector<string>> verilog;
      while (getline(newfile, tp))
      { // read data from file object and put it into string.
         vector<string> code;
         int pt1 = 0;
         while (pt1 < tp.size())
         {
            while (pt1 < tp.size() && tp[pt1] == ' ')
            {
               pt1++;
            }
            int pt2 = pt1;
            string s = "";
            while (pt2 < tp.size() && tp[pt2] != ' ')
            {
               s.push_back(tp[pt2]);
               pt2++;
            }
            if (s.size() > 0)
            {
               code.push_back(s);
            }
            pt1 = pt2;
         }
         verilog.push_back(code);
         /*for(int i=0;i<code.size();i++){
            cout<<code[i]<<" ";
         }
         cout<<endl;*/
      }

      // FINDING START AND END POINTS OF IF, ELSE IF, ELSE BLOCKS

      vector<pair<int, int>> ifStatement, elseifStatement, elseStatement;
      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "if")
         {
            int start = i + 1;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            ifStatement.push_back({start + 1, end + 1});
         }
         else if (verilog[i][0] == "else" && verilog[i].size() > 1 && verilog[i][1] == "if")
         {
            int start = i + 1;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            elseifStatement.push_back({start + 1, end + 1});
         }
         else if (verilog[i][0] == "else")
         {
            int start = i + 1;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            elseStatement.push_back({start + 1, end + 1});
         }
      }
      /*cout<<"if"<<endl;
      for(int i=0;i<ifStatement.size();i++){
         cout<<ifStatement[i].first<<" "<<ifStatement[i].second<<endl;
      }
      cout<<"else if"<<endl;
      for(int i=0;i<elseifStatement.size();i++){
         cout<<elseifStatement[i].first<<" "<<elseifStatement[i].second<<endl;
      }
      cout<<"else"<<endl;
      for(int i=0;i<elseStatement.size();i++){
         cout<<elseStatement[i].first<<" "<<elseStatement[i].second<<endl;
      }*/

      vector<vector<int>> controlFlowGraph(verilog.size() + 1);

      // IF STATEMENT

      for (int i = 0; i < ifStatement.size(); i++)
      {
         int index1 = searchElseif(elseifStatement, ifStatement[i]);
         int index2 = searchElse(elseStatement, ifStatement[i]);
         // cout<<i<<" "<<index1<<" "<<index2<<endl;
         if (index1 == -1 && index2 == -1)
         {
            controlFlowGraph[ifStatement[i].first - 1].push_back(ifStatement[i].first + 1);
            controlFlowGraph[ifStatement[i].first - 1].push_back(ifStatement[i].second + 1);
         }
         else if (index1 == -1 && index2 != -1)
         {
            controlFlowGraph[ifStatement[i].first - 1].push_back(ifStatement[i].first + 1);
            controlFlowGraph[ifStatement[i].first - 1].push_back(index2 + 2);
         }
         else if (index1 != -1 && index2 == -1)
         {
            controlFlowGraph[ifStatement[i].first - 1].push_back(ifStatement[i].first + 1);
            controlFlowGraph[ifStatement[i].first - 1].push_back(index1);
         }
      }

      // ELSE IF STATEMENT

      for (int i = 0; i < elseifStatement.size(); i++)
      {
         int index1 = searchElseif(elseifStatement, elseifStatement[i]);
         int index2 = searchElse(elseStatement, elseifStatement[i]);
         if (index1 == -1 && index2 == -1)
         {
            controlFlowGraph[elseifStatement[i].first - 1].push_back(elseifStatement[i].first + 1);
            controlFlowGraph[elseifStatement[i].first - 1].push_back(elseifStatement[i].second + 1);
         }
         else if (index1 == -1 && index2 != -1)
         {
            controlFlowGraph[elseifStatement[i].first - 1].push_back(elseifStatement[i].first + 1);
            controlFlowGraph[elseifStatement[i].first - 1].push_back(index2 + 2);
         }
         else if (index1 != -1 && index2 == -1)
         {
            controlFlowGraph[elseifStatement[i].first - 1].push_back(elseifStatement[i].first + 1);
            controlFlowGraph[elseifStatement[i].first - 1].push_back(index1);
         }
      }

      // FINDING START AND END POINTS OF SWITCH CASE STATEMENT

      vector<pair<int, int>> caseStatement;
      vector<vector<pair<string, int>>> caseValue;

      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "case")
         {
            int start = i;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "case")
               {
                  sum++;
               }
               if (verilog[end][0] == "endcase")
               {
                  sum--;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            caseStatement.push_back({start + 1, end + 1});
            sum = 0;
            vector<pair<string, int>> temp;
            for (int j = start; j <= end; j++)
            {
               if (verilog[j][0] == "case")
               {
                  sum++;
               }
               if (verilog[j][0] == "endcase")
               {
                  sum--;
               }
               if (sum == 1 && verilog[j][0][verilog[j][0].size() - 1] == ':')
               {
                  temp.push_back({verilog[j][0], j + 1});
               }
            }
            caseValue.push_back(temp);
         }
      }

      /*for(int i=0;i<caseStatement.size();i++){
         cout<<caseStatement[i].first<<" "<<caseStatement[i].second<<endl;
         for(int j=0;j<caseValue[i].size();j++){
            cout<<caseValue[i][j].first<<" "<<caseValue[i][j].second<<endl;
         }
      }*/

      // CASE STATEMENT

      for (int i = 0; i < caseStatement.size(); i++)
      {
         for (int j = 0; j < caseValue[i].size(); j++)
         {
            controlFlowGraph[caseStatement[i].first].push_back(caseValue[i][j].second);
         }
         for (int j = 0; j < caseValue[i].size(); j++)
         {
            controlFlowGraph[caseValue[i][j].second].push_back(caseValue[i][j].second + 2);
         }
      }

      // FINDING START AND END POINTS OF FOR LOOPS

      vector<pair<int, int>> forLoop;
      vector<vector<int>> forBreak;
      vector<vector<int>> forContinue;

      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "for")
         {
            int start = i;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            // cout<<start<<" "<<end<<endl;
            forLoop.push_back({start + 1, end + 1});

            vector<int> temp1, temp2;
            sum = 0;
            for (int j = start; j <= end; j++)
            {

               if (verilog[j][0] == "begin")
               {
                  sum++;
               }
               if (verilog[j][0] == "end")
               {
                  sum--;
               }
               // cout<<verilog[j][0]<<" "<<sum<<endl;
               if (sum == 2 && verilog[j][0] == "break;")
               {
                  temp1.push_back(j + 1);
               }
               if (sum == 2 && verilog[j][0] == "continue;")
               {
                  temp2.push_back(j + 1);
               }
            }
            forBreak.push_back(temp1);
            forContinue.push_back(temp2);
         }
      }

      // FOR LOOP

      for (int i = 0; i < forLoop.size(); i++)
      {
         controlFlowGraph[forLoop[i].first].push_back(forLoop[i].first + 2);
         controlFlowGraph[forLoop[i].first + 2].push_back(forLoop[i].first);
         for (int j = 0; j < forBreak[i].size(); j++)
         {
            controlFlowGraph[forBreak[i][j]].push_back(forLoop[i].second + 1);
         }
         for (int j = 0; j < forContinue[i].size(); j++)
         {
            controlFlowGraph[forContinue[i][j]].push_back(forLoop[i].first);
         }
      }

      // FINDING START AND END POINTS OF WHILE LOOPS

      vector<pair<int, int>> whileLoop;
      vector<vector<int>> whileBreak;
      vector<vector<int>> whileContinue;

      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "while")
         {
            int start = i;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            // cout<<start<<" "<<end<<endl;
            whileLoop.push_back({start + 1, end + 1});

            vector<int> temp1, temp2;
            sum = 0;
            for (int j = start; j <= end; j++)
            {

               if (verilog[j][0] == "begin")
               {
                  sum++;
               }
               if (verilog[j][0] == "end")
               {
                  sum--;
               }
               // cout<<verilog[j][0]<<" "<<sum<<endl;
               if (sum == 2 && verilog[j][0] == "break;")
               {
                  temp1.push_back(j + 1);
               }
               if (sum == 2 && verilog[j][0] == "continue;")
               {
                  temp2.push_back(j + 1);
               }
            }
            whileBreak.push_back(temp1);
            whileContinue.push_back(temp2);
         }
      }

      // WHILE LOOP

      for (int i = 0; i < whileLoop.size(); i++)
      {
         controlFlowGraph[whileLoop[i].first].push_back(whileLoop[i].first + 2);
         controlFlowGraph[whileLoop[i].first + 2].push_back(whileLoop[i].first);
         for (int j = 0; j < whileBreak[i].size(); j++)
         {
            controlFlowGraph[whileBreak[i][j]].push_back(whileLoop[i].second + 1);
         }
         for (int j = 0; j < whileContinue[i].size(); j++)
         {
            controlFlowGraph[whileContinue[i][j]].push_back(whileLoop[i].first);
         }
      }

      // FINDING START AND END POINTS OF FOREVER LOOPS

      vector<pair<int, int>> foreverLoop;
      vector<vector<int>> foreverBreak;
      vector<vector<int>> foreverContinue;

      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "forever")
         {
            int start = i;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            // cout<<start<<" "<<end<<endl;
            foreverLoop.push_back({start + 1, end + 1});

            vector<int> temp1, temp2;
            sum = 0;
            for (int j = start; j <= end; j++)
            {

               if (verilog[j][0] == "begin")
               {
                  sum++;
               }
               if (verilog[j][0] == "end")
               {
                  sum--;
               }
               // cout<<verilog[j][0]<<" "<<sum<<endl;
               if (sum == 2 && verilog[j][0] == "break;")
               {
                  temp1.push_back(j + 1);
               }
               if (sum == 2 && verilog[j][0] == "continue;")
               {
                  temp2.push_back(j + 1);
               }
            }
            foreverBreak.push_back(temp1);
            foreverContinue.push_back(temp2);
         }
      }

      // FOREVER LOOP

      for (int i = 0; i < foreverLoop.size(); i++)
      {
         controlFlowGraph[foreverLoop[i].first].push_back(foreverLoop[i].first + 2);
         controlFlowGraph[foreverLoop[i].first + 2].push_back(foreverLoop[i].first);
         for (int j = 0; j < foreverBreak[i].size(); j++)
         {
            controlFlowGraph[foreverBreak[i][j]].push_back(foreverLoop[i].second + 1);
         }
         for (int j = 0; j < foreverContinue[i].size(); j++)
         {
            controlFlowGraph[foreverContinue[i][j]].push_back(foreverLoop[i].first);
         }
      }

      // FINDING START AND END POINTS OF REPEAT LOOPS

      vector<pair<int, int>> repeatLoop;
      vector<vector<int>> repeatBreak;
      vector<vector<int>> repeatContinue;

      for (int i = 0; i < verilog.size(); i++)
      {
         if (verilog[i][0] == "repeat")
         {
            int start = i;
            int end = i + 2;
            int sum = 1;
            while (end < verilog.size() && sum != 0)
            {
               if (verilog[end][0] == "begin")
               {
                  sum++;
               }
               if (verilog[end][0] == "end")
               {
                  sum--;
               }
               if (sum == 0)
               {
                  break;
               }
               end++;
            }
            // cout<<start<<" "<<end<<endl;
            repeatLoop.push_back({start + 1, end + 1});

            vector<int> temp1, temp2;
            sum = 0;
            for (int j = start; j <= end; j++)
            {

               if (verilog[j][0] == "begin")
               {
                  sum++;
               }
               if (verilog[j][0] == "end")
               {
                  sum--;
               }
               // cout<<verilog[j][0]<<" "<<sum<<endl;
               if (sum == 2 && verilog[j][0] == "break;")
               {
                  temp1.push_back(j + 1);
               }
               if (sum == 2 && verilog[j][0] == "continue;")
               {
                  temp2.push_back(j + 1);
               }
            }
            repeatBreak.push_back(temp1);
            repeatContinue.push_back(temp2);
         }
      }

      // REPEAT LOOP

      for (int i = 0; i < repeatLoop.size(); i++)
      {
         controlFlowGraph[repeatLoop[i].first].push_back(repeatLoop[i].first + 2);
         controlFlowGraph[repeatLoop[i].first + 2].push_back(repeatLoop[i].first);
         for (int j = 0; j < repeatBreak[i].size(); j++)
         {
            controlFlowGraph[repeatBreak[i][j]].push_back(repeatLoop[i].second + 1);
         }
         for (int j = 0; j < repeatContinue[i].size(); j++)
         {
            controlFlowGraph[repeatContinue[i][j]].push_back(repeatLoop[i].first);
         }
      }

      // PRINT THE GRAPH

      map<string, int> mp;
      mp["if"]++;
      mp["elif"]++;
      mp["case"]++;
      mp["for"]++;
      mp["while"]++;
      mp["forever"]++;
      mp["repeat"]++;
      for (int i = 1; i < controlFlowGraph.size(); i++)
      {
         for (int j = 0; j < controlFlowGraph[i].size(); j++)
         {
            if (verilog[i - 1][0] == "if")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << "[ label="
                    << "\"";
               int index = searchIf(ifStatement, i);
               // cout<<index<<endl;
               if (index > controlFlowGraph[i][j])
               {
                  cout << "true";
               }
               else
               {
                  cout << "false";
               }
               cout << "\"]" << endl;
            }
            else if (verilog[i - 1][0] == "else" && verilog[i - 1].size() > 1 && verilog[i - 1][1] == "if")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << "[ label="
                    << "\"";
               int index = searchIf(elseifStatement, i);
               // cout<<index<<endl;
               if (index > controlFlowGraph[i][j])
               {
                  cout << "true";
               }
               else
               {
                  cout << "false";
               }
               cout << "\"]" << endl;
            }

            else if (verilog[i - 1][0] == "case")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  if (verilog[controlFlowGraph[i][j] - 1].size() == 1 && verilog[controlFlowGraph[i][j] - 1][0][verilog[controlFlowGraph[i][j] - 1][0].size() - 1] == ':')
                  {
                     cout << " Line" << controlFlowGraph[i][j] << ": ";
                     string s = verilog[controlFlowGraph[i][j] - 1][0];

                     cout << s << " ";
                  }
                  else
                  {
                     cout << " Line" << controlFlowGraph[i][j] << " ";
                  }
               }
               cout << "\"";
               cout << endl;
            }
            else if (verilog[i - 1][0] == "for")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << endl;
            }
            else if (verilog[i - 1][0] == "while")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << endl;
            }
            else if (verilog[i - 1][0] == "forever")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << endl;
            }
            else if (verilog[i - 1][0] == "repeat")
            {
               cout << "\" Line";
               cout << i << ": ";
               for (int k = 0; k < verilog[i - 1].size(); k++)
               {

                  cout << verilog[i - 1][k] << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << endl;
            }
            else
            {
               cout << "\"";
               if (verilog[i - 1].size() == 1 && verilog[i - 1][0][verilog[i - 1][0].size() - 1] == ':')
               {
                  cout << " Line" << i << ": ";
                  string s = verilog[i - 1][0];

                  cout << s << " ";
               }
               else
               {
                  cout << " Line" << i << " ";
               }
               cout << "\"";
               cout << " -> ";
               string s = verilog[controlFlowGraph[i][j] - 1][0];
               if (verilog[controlFlowGraph[i][j] - 1][0] == "else" && verilog[controlFlowGraph[i][j] - 1].size() > 1 && verilog[controlFlowGraph[i][j] - 1][1] == "if")
               {
                  s = "elif";
               }
               cout << "\"";
               if (mp.find(s) != mp.end())
               {
                  cout << " Line" << controlFlowGraph[i][j] << ": ";
                  if (s == "elif")
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
                  else
                  {
                     for (int k = 0; k < verilog[controlFlowGraph[i][j] - 1].size(); k++)
                     {

                        cout << verilog[controlFlowGraph[i][j] - 1][k] << " ";
                     }
                  }
               }
               else
               {
                  cout << " Line" << controlFlowGraph[i][j] << " ";
               }
               cout << "\"";
               cout << endl;
            }
            // cout<<i<<"->"<<controlFlowGraph[i][j]<<endl;*/
         }
      }

      newfile.close(); // close the file object.
   }
   return 0;
}