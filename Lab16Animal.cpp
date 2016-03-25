// Lab 16 An Improved Artificial Intelligence Program
// Programmer : Maiar Khattab
// Editor(s) used : Code Blocks 13.12
// Compiler(s) used : Code Blocks 13.12

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#include<cstring>

#include<fstream>
using std::fstream;


// struct definition
struct animal
{
    char text[100];//a yes no question
    animal* yes;//pointer to next node if answer is yes
    animal* no;//pointer to next node if answer is no
};
// function prototype
void deallocateTree(animal*);
void saveTree(animal*, fstream&);
void restoreTree(animal*, fstream&);

int main()
{
  cout << "Lab 16, Animal \n";
  cout << "Programmer: Maiar Khattab\n";
  cout << "Editor(s) used: Code Blocks 13.12\n";
  cout << "Compiler(s) used: Code Blocks 13.12\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;

  // initialize a "root" pointer named "animal* root"
  animal* root = new animal;
  // set "root" to a newly created node; set its text to "elephant", pointers to 0
  strcpy(root->text,"elephant");
  root->yes =0;
  root->no =0;
  // start a "while" loop that runs each cycle of the program
  while(true)
  {
      // invite the user to think of an animal which it will try to guess
      cout << "Think of an animal and I will guess it! Okay?(Y/N) " << endl;
      // await the user's response, and break out of the loop if he declines
      char response;
      cin >> response;
      cin.ignore(1000,10);
      if(response=='N'||response =='n')
      {
          cout << "See ya later!I guess i'm to much of a challenge" << endl;
          break;
      }

      if (response=='Y'||response=='y' )
      {
          cout<< "Get Ready ... " << endl;

      }

      // restore tree from a disk file
      fstream fin;
      fin.open("animal.dat", ios::in|ios::binary);
      restoreTree(root, fin); // create an empty root node before calling this
      fin.close();
    // declare a pointer "p" to traverse the tree, and initialize it to "root"
    animal* p = root;
    // start a loop to traverse the binary tree
    while(true)
    {
        // if p->yes is 0...
        if( p->yes == 0)
        {
            //...print p->text as the guessed animal
            cout << p->text << ",is this your animal(Y/N)?"<<endl;
            // ask user if this is correct
            char answer;
            cin >> answer;
            cin.ignore(1000,10);
            // if correct, brag and break from loop
            if(answer=='Y'||answer == 'y')
            {
                cout << "Ohhhhh Yeah, Ahhhh haaa! I'm too good"<< endl << endl;
                break;
            }
            else if(answer=='E'||answer=='e')
            {
                char e[100];
                cout << "you chose to edit the answer, please enter your new answer: " << endl;
                cin.getline(e,100);
                strcpy(p->text,e);
                cout << "Answer edit is complete." << endl;
                continue;
            }



          // ask user what animal he was thinking of...
          cout << "What animal were u thinking of???" <<endl;
          //...store in "char a[100]"
          char a[100];
          cin.getline(a,100);
          // ask what yes/no question differentiates "p->text" from "a"...
          cout << "What question can I ask to tell the difference between "
          << p->text << " & " << a  << endl;
          //...store in "char q[100]"
          char q[100];
          cin.getline(q,100);
          // ask which response is correct for "a" -- yes or no...
          cout << "Which response is correct for " << a << " Y/N? " << endl;
          //...store in "char yesNo"
          char yesNo;
          cin >> yesNo;
          cin.ignore(1000,10);
          // create two new nodes, names "y" and "n"
          animal* y = new animal;
          animal* n = new animal;
          // if the correct response for "a" is yes...
         if(yesNo == 'Y' || yesNo=='y')
         {
            // copy "a" into y->text
            strcpy(y->text,a);
            // copy p->text into n->text
            strcpy(n->text,p->text);
         }
        // else if the correct response is no...
        else if(yesNo =='N'||yesNo == 'n')
        {
           // copy "a" into n->text
           strcpy(n->text,a);
           // copy p->text into y->text
           strcpy(y->text,p->text);
        }
        // copy "q" into p->text
        strcpy(p->text,q);
        // set y->yes, n->yes, y->no, and n->no to 0
        y->yes =0;
        n->yes=0;
        y->no =0;
        n->no =0;
        // set p->yes to y and p->no to n
        p->yes = y;
        p->no = n;
       // break from loop
       break;
       //end of big if
     }
      // else if p->yes is not 0
      else if(p->yes != 0)
      {
          // print p->text as a question
          cout<< p->text << " ? " << endl;
          // ask for a yes/no reply...
          cout <<"Y/N: ";
          //...store in "char yesNo"
          char yesNo;
          cin >>yesNo;
          cin.ignore(1000,10);
          // if "yes", set p to p->yes
          //animal* yes;

          if(yesNo== 'y'|| yesNo =='Y')
            p = p->yes;
            else if(yesNo=='E'||yesNo=='e')
            {
                char Qedit[100];
                cout << "Enter your edited question: " << endl;
                cin.getline(Qedit,100);
                cout << "Question Editing complete"<<endl;
                strcpy(p->text,Qedit);
            }
            else if(yesNo=='D'||yesNo == 'd')
            {
                cout << "You selected to delete this question are you sure?";
                char dAns;
                cin >> dAns;
                cin.ignore(1000,10);
                if(dAns == 'y'||dAns == 'Y')
                {
                    deallocateTree(p->yes);
                    deallocateTree(p->no);
                    char d[100] = "To be determined";
                    strcpy(p->text,d);


                }
               else if (dAns == 'n'||dAns=='N')
                {
                    cout << "No deletion will be made" << endl;
                }
                    p->yes =0;
                    p->no = 0;

            }


          // else set p to p->no
          else
            p = p->no;
      }

    }// reclaim memory
    // save tree to a disk file
    fstream fout;
    fout.open("animal.dat", ios::out|ios::binary);
    saveTree(root, fout);
    fout.close();

 }
  deallocateTree(root);
}

void deallocateTree(animal* a)
{
  if (!a) return;
  deallocateTree(a->yes);
  deallocateTree(a->no);
  delete a;
}
void saveTree(animal* a, fstream& out) // saves tree to disk file
{
  if (a)
  {
    out.write((char*)a, sizeof(animal));
    saveTree(a->yes, out);
    saveTree(a->no, out);
  }
}
void restoreTree(animal* a, fstream& in) // loads tree from disk file
{
  in.read((char*)a, sizeof(animal));
  if(a->yes)
  {
    restoreTree(a->yes = new animal, in);
    restoreTree(a->no = new animal, in);
  }
}
