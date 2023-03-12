#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    // TODO
    // This function should create a new empty window in the browser. 
    // The window that is created should be made the first element of the list.
    windows.prepend(Window());
}

void Browser::closeWindow() {
    // TODO
    // This function should destroy the first window of the browser.
    if (windows.isEmpty()) return ;
    
    // if (windows.getNodeAtIndex(0))
        windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {
    // TODO
    // This function should make the given window the first window of the browser.
    windows.moveToIndex(index, 0);

}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    // TODO
    // This function closes the active tab of the from window, and 
    // create a new tab with the same data in the to window. 
    // If from becomes empty after its active tab is closed, then you
    // should leave it empty (to be later closed by closeEmptyWindows).
  
    if (!from.isEmpty()){
        // activeTab'i son tab olarak al
        to.newTab(from.getActiveTab());
        from.closeTab();
    }
    

}

void Browser::mergeWindows(Window &window1, Window &window2) {
    // TODO
    // you should add the tabs of window2 to window1. 
    // You shouldn’t change the order of the tabs in window1
    // tabs from window2 must come after the tabs of window1 in its list.
    
    // assume the last tab of the window that will receive the tab(s) is already the activeTab

    LinkedList<Tab> tempList;
    
    // You should close the tabs of window2
    // it should be empty after all the tabs have been moved
    while(!window2.isEmpty()){
        tempList.prepend(window2.getActiveTab());
        window2.closeTab();
    }

    Node<Tab> *temp = tempList.getFirstNode();

    do {
        window1.newTab(temp->data);
        temp = temp->next;
    }
    while (temp != tempList.getFirstNode());
    
    tempList.removeAllNodes();
}

void Browser::mergeAllWindows() {
    // TODO
    // This function merges all the windows of the browser into a single window. 
    // Tabs of all the windows in the browser must be put into the first window.

    int size =  windows.getSize();
    Node<Window> * firstNode = windows.getFirstNode();
    Node<Window> * temp = windows.getFirstNode();
    
    temp = temp->next;
    
    for (int i=1; i<size; i++){
        mergeWindows(firstNode->data, temp->data);
        temp = temp->next;
    }
    firstNode = NULL;
    temp =  NULL;
    delete firstNode;
    delete temp;
}

void Browser::closeAllWindows() {
    // TODO
    windows.removeAllNodes();
}

void Browser::closeEmptyWindows() {
    // TODO
    // This function should look for empty windows in the browser, and
    // close any empty windows that is finds. 
    // If there aren’t any empty windows in the browser, then do nothing.
    int size =  windows.getSize();
    if (size == 0) return ;
    Node<Window> * temp = windows.getFirstNode();
    
    for (int i=0; i<size; i++){
        if (temp == NULL) return ;
        if ((temp->data).isEmpty()) windows.removeNode(temp);
        if (i != size-1) temp = temp->next;
    }
    /*
    Node<Window> * temp = windows.getFirstNode();
    if(temp == NULL) {
        return ;
    } else {
        if (temp->data.isEmpty())
            windows.removeNode(temp);
        else if (((temp->data).getActiveTab().getUrl() == "" &&
                                      (temp->data).getActiveTab().getTitle() == "" &&
                                      (temp->data).getActiveTab().getContents() == "")))
            
            
        temp = temp->next;
        while(temp != windows.getFirstNode()) {
            if (temp == NULL) return ;
            if ((temp->data).isEmpty())  windows.removeNode(temp);
            temp = temp->next;
        }
    }
    */
}


void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
