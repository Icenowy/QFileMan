#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
#include <QFileInfo>

namespace Ui {
class Preview;
}

class Preview : public QWidget
{
    Q_OBJECT
    
public:
    explicit Preview(QWidget *parent = 0);
    ~Preview();
    void DoPreview(const QFileInfo &fi);
    void Clean();
    
private:
    Ui::Preview *ui;
    void DoPreview_WebView(const QFileInfo &fi);
    void DoPreview_LabelImage(const QFileInfo &fi);
};

#endif // PREVIEW_H
