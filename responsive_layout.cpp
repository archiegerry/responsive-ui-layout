//
// Created by Archie Gerry for UI CWK1 on 24/11/2022
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>

//using namespace std;

      //Refers to the padding offset between buttons
const int offset = 5;
      //Refers to the standard width and height of a normal button
      int standardWidth = 60;
      int standardHeight = 30;
      //Refers to the compact width and height of a smaller button
      int compactWidth = 40;
      int compactHeight = 20;
      //Refers to the width of the advert
      int advertWidth = 100;


//checks to see if the search boxes will exceed the end of the screen for standard box sizes
int ResponsiveLayout::checkStandardDimensions(const QRect &r, int labelCount)
{

    //checks to see if the lables will exceed the screen real estate
    // the (offset+advertWidth+offset) accounts for the advert on the left
    if (((labelCount+1) * (standardWidth+offset)) + (offset+advertWidth+offset) > r.width() - (offset+advertWidth+offset)) {
        return 1;
    } else {
    return 0;
    }
}

//checks to see if the search boxes will exceed the end of the screen for compact box sizes
int ResponsiveLayout::checkCompactDimensions(const QRect &r, int labelCount)
{

    //checks to see if the lables will exceed the screen real estate
    // the (offset+advertWidth+offset) accounts for the advert on the left
    if (((labelCount+1) * (compactWidth+offset)) + (offset+advertWidth+offset) > r.width() - (offset+advertWidth+offset)) {
        return 1;
    } else {
    return 0;
    }
}

//Display for compact sizes
void ResponsiveLayout::compactLayout(const QRect &r)
{
    //Sets the geometry of the rectangle based on the window size
    QLayout::setGeometry(r);
    //labelX refers to the X position, labelY refers to the Y position, widthcount and heightcount count the results already displayed in each axis
    int labelX = 0, labelY = 20, widthCount = 0, heightCount = 0;
    //scale allows the results to scale
    float scale = 3.75f;

    //This will get rid of any visual artifacts when changing between windows sizes
    for (int i = 0; i < list_.size(); i++) {QLayoutItem *o = list_.at(i); ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget()); label ->setGeometry(-1,-1,0,0);}

    //Loop to display all of the relevant labels
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            //Sets the width of the navigation tab to be proportional to window size
            int navTabWidth = r.width() - 200;

            //Displays the nav tabs
            if (label -> text() == kNavTabs) {
                label -> setGeometry(offset + compactWidth + offset, r.y() + offset, navTabWidth, standardHeight);

            //Displays the home button
            } else if (label -> text() == kHomeLink) {
                label -> setGeometry(offset, r.y() + offset, compactWidth, standardHeight);

            //Displays the search bar
            } else if (label -> text() == kSearchText) {
                label -> setGeometry(offset + compactWidth + offset, 50, r.width() - 165, compactHeight);

            //Displays the search button
            } else if (label -> text() == kSearchButton) {
                label -> setGeometry(80 + (r.width() - 190), 50, standardWidth - 5, compactHeight);

            //Displays the menu button
            } else if (label -> text() == kMenu) {
                label -> setGeometry(55 + navTabWidth, r.y() + offset, compactWidth, standardHeight);

            //Displays the sign in button
            } else if (label -> text() == kSignIn) {
                label -> setGeometry(100 + navTabWidth, r.y() + offset, compactWidth+5, standardHeight);

            //Displays the shopping basket button
            } else if (label -> text() == kShoppingBasket) {
                label -> setGeometry(150 + navTabWidth, r.y() + offset, compactWidth+5, standardHeight);

            //Displays the search resultys
            } else if (label -> text() == kSearchResult)
            {

                //Increases the X potition if there is more than one reult already there
                if (widthCount > 0)
                    labelX = labelX + offset + compactWidth*scale;

                //Prevents the results from exceeding border size
                if (((widthCount+1) * (offset + compactWidth*scale)) + offset > r.width())
                {
                    widthCount = 0;
                    labelX = 0;
                    labelY = labelY + compactHeight*scale + offset;
                    heightCount++;
                }

                //checks to see if the label height will overlap with the page arrows
                if ((heightCount * (offset + compactHeight*scale)) + 200 < r.height())
                {
                    //set the label with the new dimensions plus the offsets
                    label -> setGeometry(offset + labelX, r.y() + 70 + labelY, compactWidth*scale, compactHeight*scale);
                    widthCount++;
                } else
                {
                    label -> setGeometry(-1,-1,0,0);
                }

            //Displays the search forward button
            } else if (label -> text() == kSearchForward) {
                label -> setGeometry((floor(r.width() * 4 / 6)) + (offset*2), r.height() - (offset + compactHeight + offset), compactWidth, compactHeight);

            //Displays the search backward button
            } else if (label -> text() == kSearchBackward) {
                label -> setGeometry((floor(r.width() / 6)) - offset, r.height() - (offset + compactHeight + offset), compactWidth, compactHeight);

            //Displays the page number
            } else if (label -> text() == kPageNumber) {
                label -> setGeometry((floor(r.width() / 2) - standardWidth - offset), r.height() - (offset + compactHeight + offset), standardWidth*2, compactHeight);

            //some other buttons had to be removed for a beautiful compact layout!
            } else {
                label -> setGeometry(-1,-1,0,0);
            }

        }  catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }

    }
}

//for vertical sizes
void ResponsiveLayout::verticalLayout(const QRect &r)
{
    //Sets the geometry of the rectangle based on the window size
    QLayout::setGeometry(r);
    int labelX = 0, labelY = 20, widthCount = 0, heightCount = 0;
    float scale = 1;

    //gets rid of any visual artifacts
    for (int i = 0; i < list_.size(); i++) {QLayoutItem *o = list_.at(i); ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget()); label ->setGeometry(-1,-1,0,0);}

    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            int navTabWidth = r.width() - 200;

            //Displays the nav tabs
            if (label -> text() == kNavTabs) {
                label -> setGeometry(offset + compactWidth + offset, r.y() + offset, navTabWidth, standardHeight);

            //Displays the home button
            } else if (label -> text() == kHomeLink) {
                label -> setGeometry(offset, r.y() + offset, compactWidth, standardHeight);

            //Displays the search bar
            } else if (label -> text() == kSearchText) {
                label -> setGeometry(offset + compactWidth + offset, 50, r.width() - 165, compactHeight);

            //Displays the search button
            } else if (label -> text() == kSearchButton) {
                label -> setGeometry(80 + (r.width() - 190), 50, standardWidth - 5, compactHeight);

            //Displays the menu button
            } else if (label -> text() == kMenu) {
                label -> setGeometry(55 + navTabWidth, r.y() + offset, compactWidth, standardHeight);

            //Displays the sign in button
            } else if (label -> text() == kSignIn) {
                label -> setGeometry(100 + navTabWidth, r.y() + offset, compactWidth+5, standardHeight);

            //Displays the shopping basket button
            } else if (label -> text() == kShoppingBasket) {
                label -> setGeometry(150 + navTabWidth, r.y() + offset, compactWidth+5, standardHeight);

            //Displays the search results
            } else if (label -> text() == kSearchResult)
            {

                if (widthCount > 0)
                    labelX = labelX + offset + compactWidth*scale;

                if (((widthCount+1) * (offset + compactWidth*scale)) + offset > r.width())
                {
                    widthCount = 0;
                    labelX = 0;
                    labelY = labelY + compactHeight*scale + offset;
                    heightCount++;
                }

                //checks to see if the label height will overlap with the arrows
                if ((heightCount * (offset + compactHeight*scale)) + 180 < r.height())
                {
                    //set the label with the new dimensions plus the offsets
                    label -> setGeometry(offset + labelX, r.y() + 70 + labelY, compactWidth*scale, compactHeight*scale);
                    widthCount++;
                } else
                {
                    label -> setGeometry(-1,-1,0,0);
                }


            //Displays the search forward button
            } else if (label -> text() == kSearchForward) {
                label -> setGeometry((floor(r.width() * 4 / 6)) + (offset*2), r.height() - (offset + compactHeight + offset), compactWidth, compactHeight);

            //Displays the search backward button
            } else if (label -> text() == kSearchBackward) {
                label -> setGeometry((floor(r.width() / 6)) - offset, r.height() - (offset + compactHeight + offset), compactWidth, compactHeight);

            //Displays the page number
            } else if (label -> text() == kPageNumber) {
                label -> setGeometry((floor(r.width() / 2) - standardWidth - offset), r.height() - (offset + compactHeight + offset), standardWidth*2, compactHeight);

            } else {
                label -> setGeometry(-1,-1,0,0);
            }

        }  catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }

    }

    //all labels must be displayed to ensure advert is on the bottom
    for (int i = 0; i < list_.size(); i++)
    {
        QLayoutItem *o = list_.at(i);
        ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

        if (label -> text() == kAdvert)
        {
            if (labelY + r.height() - 300 - (compactHeight*2+standardHeight+offset*7) < r.height() - (offset + compactHeight + offset))
                label -> setGeometry(offset + r.x(), labelY + r.y() + compactHeight*2 + standardHeight + offset*6, r.width() - offset*2, r.height() - 300 - (compactHeight*2+standardHeight+offset*8));
        }
    }
}

//for horizontal sizes
void ResponsiveLayout::horizontalLayout(const QRect &r)
{
    QLayout::setGeometry(r);
    int labelX = 0, labelY = 0, widthCount = 0, heightCount = 0;

    //gets rid of any visual artifacts
    for (int i = 0; i < list_.size(); i++) {QLayoutItem *o = list_.at(i); ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget()); label ->setGeometry(-1,-1,0,0);}

    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);

        try {
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
            int navTabWidth = r.width() - 335;

            // displays the navigation tabs
            if (label -> text() == kNavTabs )
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset, r.y() + offset, navTabWidth, standardHeight);

            //displays the home button
            else if (label -> text() == kHomeLink)
                label -> setGeometry(offset, r.y() + offset, standardWidth, standardHeight);

            //displays the exit button
            else if (label -> text() == kExit)
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset + navTabWidth + offset + standardWidth + offset + + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            //displays the sign in button
            else if (label -> text() == kSignIn)
                label -> setGeometry(standardWidth*2 + navTabWidth + offset*4, r.y() + offset, standardWidth, standardHeight);

            //displays the menu button
            else if (label -> text() == kMenu)
                label -> setGeometry(offset + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            //displays the shopping basket button
            else if (label -> text() == kShoppingBasket)
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset + navTabWidth + offset + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            //displays the search query
            else if (label -> text() == kSearchText) {
                label -> setGeometry(offset + compactWidth + offset, 50, r.width() - 165, compactHeight);

            //displays the search button
            } else if (label -> text() == kSearchButton) {
                label -> setGeometry(80 + (r.width() - 190), 50, standardWidth - 5, compactHeight);


            }
                else if (label -> text() == kSearchResult )
                {
                    //increase the x position if there is more than one label
                    if (widthCount > 0)
                    {
                        labelX = labelX + compactWidth + offset;
                    }

                    //checks to see if the label will exceed screen size
                    if (checkCompactDimensions(r, widthCount) == 1)
                    {
                        //if so increase the y direction and reset the x position
                        labelY = labelY + compactHeight + offset;
                        labelX = 0;
                        widthCount = 0;
                        heightCount++;
                    }

                    //checks to see if the label height will overlap with the arrows
                    if ((heightCount * (offset + compactHeight)) + 150 < r.height())
                    {
                        //set the label with the new dimensions plus the offsets
                        label -> setGeometry(offset + 100 + offset + labelX + r.x(), 90 + labelY + r.y(), compactWidth, compactHeight);
                        widthCount++;
                    } else
                    {
                        labelY = labelY - compactHeight - offset;
                    }

            //displays the back button
            } else if (label -> text() == kSearchBackward) {
                label -> setGeometry((floor(r.width() / 2) - compactWidth*8 - offset*5), r.height() - (offset + standardHeight + offset), standardWidth*4, compactHeight);

            //displays the forward button
            } else if (label -> text() == kSearchForward) {
                label -> setGeometry((floor(r.width() / 2) + compactWidth + offset), r.height() - (offset + standardHeight + offset), standardWidth*4, compactHeight);

            //displays the page number
            } else if (label -> text() == kPageNumber) {
                label -> setGeometry((floor(r.width() / 2) - compactWidth*2 - offset*2), r.height() - (offset + standardHeight + offset), standardWidth*2, compactHeight);

            //no adverts in the compact layout!
            } else if (label -> text() == kAdvert) {
                label -> setGeometry(r.x() + r.width() - (offset+advertWidth+offset), r.y() + standardHeight*2 + offset*6, 100, r.height() - 145);

            //displays the search options
            } else if (label -> text() == kSearchOptions) {
                label -> setGeometry(offset + r.x(), r.y() + standardHeight*2 + offset*6, 100, r.height() - 145);

            } else {
                label -> setGeometry(-1,-1,0,0);

            }

        }  catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }

    }
}

//for every other size
void ResponsiveLayout::standardLayout(const QRect &r)
{

    //sets the screen geometry
    QLayout::setGeometry(r);
    //refreshes the screen to avoid any visual artifacts
    for (int i = 0; i < list_.size(); i++) {QLayoutItem *o = list_.at(i); ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget()); label ->setGeometry(-1,-1,0,0);}
    //establishes the variables
    int labelX = 0, labelY = 0, widthCount = 0;


    // for all the Widgets added in ResponsiveWindow.cpp
    for (int i = 0; i < list_.size(); i++) {

        QLayoutItem *o = list_.at(i);
        int navTabWidth = r.width() - (offset*7) - (standardWidth*5);

        try {
            // cast the widget to one of our responsive labels
            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

            // null: cast failed on pointer
            if (label == NULL)
                std::cout << "warning, unknown widget class in layout" << std::endl;

            // displays the navigation tabs
            else if (label -> text() == kNavTabs )
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset, r.y() + offset, navTabWidth, standardHeight);

            //displays the home button
            else if (label -> text() == kHomeLink)
                label -> setGeometry(offset, r.y() + offset, standardWidth, standardHeight);

            //displays the exit button
            else if (label -> text() == kExit)
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset + navTabWidth + offset + standardWidth + offset + + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            //displays the sign in button
            else if (label -> text() == kSignIn)
                label -> setGeometry(standardWidth*2 + navTabWidth + offset*4, r.y() + offset, standardWidth, standardHeight);

            //displays the menu button
            else if (label -> text() == kMenu)
                label -> setGeometry(offset + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            //displays the shopping basket button
            else if (label -> text() == kShoppingBasket)
                label -> setGeometry(offset + standardWidth + offset + standardWidth + offset + navTabWidth + offset + standardWidth + offset, r.y() + offset, standardWidth, standardHeight);

            // displays the search button
            else if (label -> text() == kSearchButton)
                label -> setGeometry(75 + (r.width() - 205), r.y() + offset + standardHeight + offset*2, standardWidth, standardHeight);


            // displays the search results
            else if (label -> text() == kSearchResult )
            {
                //increase the x position if there is more than one label
                if (widthCount > 0)
                {
                    labelX = labelX + 65;
                }

                //checks to see if the label will exceed screen size
                if (checkStandardDimensions(r, widthCount) == 1)
                {
                    //if so increase the y direction and reset the x position
                    labelY = labelY + 45;
                    labelX = 0;
                    widthCount = 0;
                }

                //checks to see if the label height will overlap with the arrows
                if (labelY + 210 < r.height())
                {
                    //set the label with the new dimensions plus the offsets
                    label -> setGeometry(offset + 100 + offset + labelX + r.x(), 90 + labelY + r.y(), 60, 40);
                    widthCount++;
                } else
                {
                    labelY = labelY - 45;
                }
            }

            // displays the search text box
            else if (label -> text() == kSearchText )
                label -> setGeometry(offset + standardWidth + offset, r.y() + standardHeight + offset*3, r.width() - 205, standardHeight);

            // displays the search options
            else if (label -> text() == kSearchOptions )
                label -> setGeometry(offset + r.x(), r.y() + standardHeight*2 + offset*6, 100, r.height() - 145);

            //displays the page number
            else if (label -> text() == kPageNumber)
                label -> setGeometry((floor(r.width() / 2) - standardWidth - offset), r.height() - (offset + standardHeight + offset), standardWidth*2, standardHeight);

            //displays the back button
            else if (label -> text() == kSearchBackward)
                    label -> setGeometry((floor(r.width() / 2) - standardWidth*3 - offset*3), r.height() - (offset + standardHeight + offset), standardWidth*2, standardHeight);

            //displays the forward button
            else if (label -> text() == kSearchForward)
                    label -> setGeometry((floor(r.width() / 2) + standardWidth + offset), r.height() - (offset + standardHeight + offset), standardWidth*2, standardHeight);

            // otherwise: disappear label by moving out of bounds
            else if (label -> text() == kAdvert)
                    label -> setGeometry(r.x() + r.width() - (offset+advertWidth+offset), r.y() + standardHeight*2 + offset*6, 100, r.height() - 145);

            else
                    label -> setGeometry (-1,-1,0,0);

        }
        catch (std::bad_cast) {
            // bad_cast: cast failed on reference...
            std::cout << "warning, unknown widget class in layout" << std::endl;
        }
    }
}


//Determines which layout the current screen size falls into
void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);

    //horizontal dimensions
    if (r.width() > 700 && r.height() <= 400)
    {
        horizontalLayout(r);
    }

    //vertical dimensions
    else if (r.width() < 550 && r.height() >= 450)
    {
        verticalLayout(r);
    }

    //compact dimensions
    else if (r.width() < 700 && r.height() < 450)
    {
        compactLayout(r);
    }

    //standard layout
    else
    {
        standardLayout(r);
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
