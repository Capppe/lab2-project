#ifndef RADIOINTERFACE_HPP
#define RADIOINTERFACE_HPP

#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QStringList>
#include <QComboBox>
#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QPair>
#include <QDir>

#include "../customWidgets/customButton.hpp"
#include "dataStorage.hpp"
#include "APIhandler.hpp"

class RadioInterface : public QWidget
{
    Q_OBJECT

public:
    RadioInterface();
    ~RadioInterface();
    
private:
    void initVars();
    void createLayout();
    void createButtons();
    void styleLayout();
    void styleSecondLayout();
    void bindButtons();
    void bindSignals(CustomButton *button);
    void setButtonStyling(CustomButton *button);
    void stopRadio();
    void createSecondLayout();
    
    void createThirdLayout();
    void addLangData(QStringList data);
    void addCountryData(QStringList data);
    void langApiCall();
    void countryApiCall();
    void styleThirdLayout();

    APIHandler *apiHandler;

    QVBoxLayout *mainLayout;
    QGridLayout *buttonLayout;
    QHBoxLayout *npLayout;
    QVBoxLayout *firstLayout;
    QLabel *np;
    QLabel *npText;
    QPushButton *stopButton;
    QPushButton *browseButton;

    QWidget *buttonWidget;
    QWidget *npWidget;
    QWidget *firstWidget;
    QStackedWidget *stackedWidget;

    //Second layout
    QWidget *smainWidget;
    QVBoxLayout *smainLayout;
    QHBoxLayout *sPicLayout;
    QVBoxLayout *sinfoLayout;
    QVBoxLayout *sButtonLayout;

    QLabel *icon;
    QLabel *name;
    QLabel *address;
    QLabel *country;

    QPushButton *sstopButton;
    QPushButton *seditButton;
    
    //Third layout
    QWidget *tmainWidget;
    QVBoxLayout *tmainLayout;
    QHBoxLayout *tboxLayout;
    QScrollArea *tscrollArea;
    QComboBox *tlanguage;
    QComboBox *tcountry;
    //Input asweell

    QPushButton *tsearch;

    QLabel *tinfo;
    QLabel *ticon;
    QLabel *tcountryCode;
};

#endif
