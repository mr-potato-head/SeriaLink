#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class MenuWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit MenuWidget(QWidget *parent = 0);

  protected:
      void focusOutEvent(QFocusEvent *);

  private:

  //! Maing grid layout
  QGridLayout* main_layout_ {nullptr};

  //! About button
  QPushButton* about_button_ {nullptr};
};

#endif // MENUWIDGET_H
