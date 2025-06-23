#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define M 101

struct Word
{
  string word;       // tieng anh
  string type;       // tu loai
  string vietnamese; // tu tieng viet
};

struct DictNode
{
  Word word;
  DictNode *next;
};

void init(DictNode *head[])
{

  for (int i = 0; i < M; i++)
  {
    head[i] = NULL;
  }
}

int hashStr(string en)
{
  int h = 0;

  for (int i = 0; i < en.length(); i++)
  {
    h += (int)tolower((en[i]) * (i + 1));
  }

  return h % M;
}

int hashFunc(Word w)
{
  return hashStr(w.word);
}

// khoi tao
DictNode *createWord(Word w)
{
  DictNode *word = new DictNode;
  word->word = w;
  word->next = NULL;

  return word;
}

// them tu
void addWord(DictNode *head[], Word w)
{
  int h = hashFunc(w);
  DictNode *r = head[h]; // trỏ đến phần tử đầu tiên trong chuỗi

  DictNode *p = createWord(w);

  // them dau
  if (r == NULL)
  {
    head[h] = p;
  }
  // them cuoi
  else
  {

    while (r->next != NULL)
    {
      if (r->word.word.compare(w.word) == 0)
        break;

      r = r->next;
    }
    if (r->word.word.compare(w.word) != 0)
    {
      r->next = p;
    }
  }
}

// update
void updateWord(DictNode *head[], Word w)
{
  int h = hashFunc(w);
  DictNode *r = head[h];
  if (r != NULL)
  {
    int t = hashFunc(r->word);
    do
    {
      t = hashFunc(r->word);
      if (t == h)
      {
        r->word = w;
      }

      r = r->next;
    } while (r != NULL);
  }
}

void deleteWord(DictNode *heads[], string en)
{
  int h = hashStr(en);
  DictNode *r = heads[h];
  DictNode *prev = NULL;

  while (r != NULL)
  {

    if (r->word.word.compare(en) == 0)
    {

      if (prev == NULL) // xoa dau tien
      {
        heads[h] = r->next;
      }
      else
      { // xoa r
        prev->next = r->next;
      }
      r->next = NULL;

      delete (r);
      break;
    }
    prev = r;
    r = r->next;
  }
}

void SearchWord(DictNode *head[], string en)
{
  int h = hashStr(en);
  DictNode *r = head[h];
  while (r != NULL)
  {
    int h1 = hashFunc(r->word);
    if (h == h1)
    {
      cout << r->word.word << "(" << r->word.type << ") = " << r->word.vietnamese << endl;
      break;
    }
    r = r->next;
  }
}

void display(DictNode *head[])
{

  for (int i = 0; i < M; i++)
  {
    if (head[i] != NULL)
    {
      cout << "\n======== BUCKET " << i << "=====\n";
      DictNode *p = head[i];

      while (p != NULL)
      {
        cout << p->word.word << "(" << p->word.type << ") = " << p->word.vietnamese << endl;
        p = p->next;
      }
    }
  }
}

void readDict(DictNode *heads[])
{
  ifstream f;
  f.open("Anh_Viet.txt", ios::in);

  while (!f.eof())
  {
    Word w;
    getline(f, w.word);
    getline(f, w.type);
    getline(f, w.vietnamese);

    // Trước khi gọi addWord(dicts, w);
    if (!w.word.empty() && !w.type.empty() && !w.vietnamese.empty())
    {
      addWord(heads, w);
    }
  }

  f.close();
}

int main()
{

  cout << "TU DIEN \n";

  DictNode *dicts[M];
  init(dicts);
  readDict(dicts);
  display(dicts);
  deleteWord(dicts, "Hard");

  cout << "\n =============== sau khi xoa ==============\n";
  display(dicts);
  return 0;
}