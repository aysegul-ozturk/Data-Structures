#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
    if (isEmpty() || activeTab == -1){
        // tabs.append(Tab());
        return Tab();
    }
    if (tabs.getNodeAtIndex(activeTab))
        return tabs.getNodeAtIndex(activeTab)->data;
}

bool Window::isEmpty() const {
    // TODO
    return activeTab == -1 && tabs.isEmpty();
}

void Window::newTab(const Tab &tab) {
    // TODO
    if (isEmpty()){
        tabs.prepend(tab);
        changeActiveTabTo(0);
    }
    else{
        if (tabs.getNodeAtIndex(activeTab)){
            // tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab));
            tabs.insertAtIndex(tab, ++activeTab);
        }

    }
}

void Window::closeTab() {
    // TODO
      if(activeTab != -1) {
        // TODO
        if (tabs.getSize() > 1){
          if (activeTab == tabs.getSize()-1){
            tabs.removeNodeAtIndex(activeTab);
            // Eger active tab son tabsa, daha ileri gidemeyecegi icin 
            // yeni son tab active tab olmaya devam ediyor.
            activeTab = tabs.getSize()-1;
          }
          else if (activeTab < tabs.getSize()-1){
            tabs.removeNodeAtIndex(activeTab);
          }
        }
        else if (tabs.getSize() == 1){
          tabs.removeAllNodes();
          activeTab = -1;
        }
        else if(tabs.getSize() == 0){
          activeTab = -1;
        }
    }
}

void Window::moveActiveTabTo(int index) {
    // TODO
    if (isEmpty())  return;
    if (activeTab == -1)  return;
    if (index > tabs.getSize() - 1){
        tabs.moveToIndex(activeTab, tabs.getSize() - 1);
        activeTab = tabs.getSize() - 1;
    }
    else{
        tabs.moveToIndex(activeTab, index);
        activeTab = index;
    }
    /*
         if(activeTab != -1) {
        if(index > tabs.getSize()-1) return;
        if (activeTab == index) return;
        if (isEmpty()) return;
    
        tabs.moveToIndex(activeTab, index);
        activeTab = index;
    }
    */
}

void Window::changeActiveTabTo(int index) {
    // TODO
        if (index > tabs.getSize() -1 || index < -1) return ;
        else if(tabs.getNodeAtIndex(index)) activeTab = index;
}

void Window::addTab(Node<Tab> &tab) {
    // TODO
    // add the tab as the last tab
    if (this->isEmpty()) activeTab = 0;
    tabs.append(tab.data);
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
