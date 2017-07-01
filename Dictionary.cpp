#include<iostream>
#include<string.h>
#include<time.h>
#include<cstdio>   //printf()
#include<unistd.h> //sleep()
#include<stdlib.h> //system("clear")

using namespace std;
typedef struct node
{
   char word[25];
   char meaning[100];
   node *left;
   node *right;
   
}node;


void loadDictionary();
node *getTreeFromSavedFile();
void separateWord(char[],char[],char[]);
node *createNode(char[],char[]);
void addWord(node *,char[],char[]);
node *searchWord(node *,char[]);
void TreeToFile(node*);
void writeDataToFile(node *,FILE*);
void printAllWords(node *); 

int main()
{  
   system("clear");
  // loadDictionary();
   char word[25],meaning[100];
   node *temp=getTreeFromSavedFile();
   if(temp==NULL)
   {
       cout<<"FileNotFoundException\nor,Dictionary is Empty"<<endl;
   }
   while(1)
   {
       cout<<"WELCOME TO MONGLO DICTIONARY"<<endl;
       cout<<"MENU"<<endl;
       cout<<"<1> ADD A WORD"<<endl;
       cout<<"<2> SEARCH WORD"<<endl;
       cout<<"<3> PRINT ALL WORDS"<<endl;
       cout<<"<4> SAVE AND EXIT"<<endl;
       int choice;
       cout<<"Enter Choice :";
       cin>>choice;
       switch(choice)
       {
          case 1:
                   cout<<"Enter Word : ";
                   cin>>word;
                   cout<<"\nEnter Meaning : ";
                   cin>>meaning;
                   if(temp==NULL)
                   {
                      temp=createNode(word,meaning);
                   }
                   else
                   {
                      addWord(temp,word,meaning);
                   }
                   break;
  
          case 2:
                  if(temp==NULL)
                  {
                     cout<<"Dictionary Is Empty."<<endl;
                  }
                  else
                  {
                     cout<<"Enter Word : ";
                     cin>>word;
                     node *w=searchWord(temp,word);
                     if(w==NULL)
                     {
                        cout<<"Word Not Found."<<endl;
                     }
                     else
                     {
                        cout<<w->word<<endl;
                        puts(w->meaning);
                     }
                  }
                  break;
                  
          case 3: 
                  if(temp==NULL)
                  {
                     cout<<"DICTIONARY IS EMPTY."<<endl; 
                  }
                  else
                  {
                     cout<<"WORDS IN THE DICTIONARY"<<endl;
                     printAllWords(temp);
                  }
                  break;
                  
          case 4:
                  TreeToFile(temp);
                  exit(0);
                  break;
                  
          default:
                  cout<<endl<<"Enter Choice :";
                  cin>>choice; 
                  
         }
     
    }
   return 0;
}



/*void SetCursorPos(int XPos, int YPos)
{
 printf("\033[%d;%dH", YPos+1, XPos+1);
}

/*void loadDictionary()
{
   int i;
   system("clear");
   SetCursorPos(20,20);
   cout<<"DICTIONARY LOADING";
   for(i=0;i<50;i++)
   {
     SetCursorPos(15+i,21);
     cout<<"???";
     SetCursorPos(20,22);
     cout<<2*i<<"% completed";
     sleep(1);
   }
}*/

node *getTreeFromSavedFile() //extract tree from saved dictionary file
{
   node *tree=NULL;
   char word[25],meaning[100],text[125];
   char *str;
   int flag=0;
   FILE *file=fopen("/home/anubhav55182/Desktop/PersonalDictionary.txt","r");
   if(file==NULL)
   {
       tree=NULL;
   }
   else
   {
       while(!feof(file))
       {
          str=fgets(text,125,file);
          if(str==NULL)
          {
             break;
          }
          separateWord(text,word,meaning);
          if(flag==0)
          {
             tree=createNode(word,meaning);
             flag=1;
          }
          else
          {
             addWord(tree,word,meaning);
          }
          
       }
       
       fclose(file);
   }
   return tree;
}

void separateWord(char text[],char word[],char meaning[])
{
   int i,j;
   for(i=0;text[i]!=' ';i++)
   {
      word[i]=text[i];
   }
   word[i++]='\0';
   for(int j=0;text[i]!=' ';i++,j++)
   {
      meaning[j]=text[i];
   }
   meaning[j]='\0';
}


node *createNode(char word[],char meaning[]) //creating a new node for insertion
{
   node *newNode=new node();
   strcpy(newNode->word,word);
   strcpy(newNode->meaning,meaning);
   newNode->left=NULL;
   newNode->right=NULL;
   return newNode;
}



void addWord(node *tree,char word[],char meaning[]) //add a new word which is not there in dict
{
   node *p,*q;
   p=q=tree;
   while(strcmp(word,p->word)!=0 && p!=NULL)
   {
      q=p;
      if(strcmp(word,p->word)<0)
      {
          p=p->left;
      }
      else
      {
         p=p->right;
      }
   }
   if(strcmp(word,p->word)==0)
   {
      cout<<"Word Already Exists..."<<endl;
      sleep(1);
   }
   else if(strcmp(word,p->word)<0)
   {
      q->left=createNode(word,meaning);
   }
   else
   {
      q->right=createNode(word,meaning);
   }
}


node *searchWord(node *tree,char word[])
{
   node *p=tree;
   while(p!=NULL)
   {
      if(strcmp(word,p->word)<0)
      {
         p=p->left;
      }
      else if(strcmp(word,p->word)>0)
      {
         p=p->right;
      }
      if(strcmp(word,p->word)==0)
      {
         break;
      }
   }
   return p;
}

void TreeToFile(node *tree)
{
   
   FILE *file=fopen("/home/anubhav55182/Desktop/PersonalDictionary.txt","w");
   if(file==NULL)
   {
      cout<<"Error opening the file."<<endl;
   }
   else
   {
      if(tree!=NULL)
      {
         writeDataToFile(tree,file);
      }
   }
   fclose(file);
}

void writeDataToFile(node *tree,FILE *file)
{
   if(tree!=NULL)
   {
      fprintf(file,"%s %s",tree->word,tree->meaning);
      writeDataToFile(tree->left,file);
      writeDataToFile(tree->right,file);
   }
}


void printAllWords(node * tree)
{
   cout<<"WORDS IN THE DICTIONARY"<<endl;
   while(tree!=NULL)
   {
      printAllWords(tree->left);
      cout<<"["<<tree->word<<"]"<<"\t\t"<<"["<<tree->meaning<<"]"<<endl;
      printAllWords(tree->right);
   }
}
















