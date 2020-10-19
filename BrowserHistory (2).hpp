#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>     // std::next, std::prev
#include <list>

using std::string;
using namespace std;

struct WebPage {      // creating struct that holds URL and webpage size
  string _url;
  size_t _pSize;
  WebPage(string url, size_t filesize): _url(url), _pSize(filesize) {}
};

class BrowserHistory {
public:
    BrowserHistory();

    void visitSite(string url, size_t filesize);
    void backButton();
    void forwardButton();

    void readFile(string fileName);

    string currentUrl();
    size_t currentPageSize();
    size_t getHistoryLength();

private:
  // TO BE COMPLETED
  list<WebPage> history;
  list<WebPage>::iterator currPage;
  ifstream myfile;      // for reading from a file
  string url;
  size_t filesize;
  string command;       // holder for visit, back, and forward commands when reading from file
};

BrowserHistory::BrowserHistory(){
  currPage = history.begin();       // have iterator start at beginning of list
}

void BrowserHistory::visitSite(string url, size_t filesize){
  if(currPage != prev(history.end())){          // check if iterator is in the middle of list
    history.erase(++currPage, history.end());             // erase history after current position
    history.insert(++currPage, WebPage(url, filesize));   // insert new page after current position
  }else{                    // executes if iterator is not in the middle of list
    history.push_back(WebPage(url, filesize));    // add new page
    currPage = prev(history.end());               // set iterator to newly added page
  }
}

void BrowserHistory::backButton() {
  if(!history.empty() && currPage != history.begin()){    // if list is not empty and iterator is not at the first page
    currPage--;                                           // move iterator to previous page
  }
  if(currPage == history.begin()){    // if the list is empty or there is only one page in history
    currPage = history.begin();       // have iterator remain at the beginning of list
  }
}

void BrowserHistory::forwardButton() {
  if(currPage != prev(history.end()) && !history.empty()){  // if the iterator is not at the end and list is not empty
    currPage++;                                             // move iterator to the next page
  }
  if(currPage == prev(history.end())){    // if iterator is at the end of list
    currPage = prev(history.end());       // have iterator remain at the end of list
  }
}

string BrowserHistory::currentUrl() {
  if(history.empty()){        // if list is empty, return empty string
    return "";
  }else{                      // if list is not empty, return url at iterator's position
    return currPage->_url;
  }
}

size_t BrowserHistory::currentPageSize() {
  if(history.empty()){        // if list is empty, return 0
    return 0;
  }else{                      // if list is not empty, return webpage size at iterator's position
    return currPage->_pSize;
  }
}

size_t BrowserHistory::getHistoryLength() {
  return history.size();        // return length of list (how many webpages are in list)
}

void BrowserHistory::readFile(string filename){
  myfile.open(filename);      // open file

  while(myfile >> command >> url >> filesize){

      if(command == "visit"){       // visit command adds webpage to list
        visitSite(url, filesize);
      }

      if(command == "back"){        // back comand moves iterator to previous webpage
        backButton();
      }

      if(command == "forward"){     // forward command moves iterator to next webpage
        forwardButton();
      }

  }
  myfile.close();
}
