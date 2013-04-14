#include "preview.h"
#include "ui_preview.h"

Preview::Preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preview)
{
    ui->setupUi(this);
    Clean();
}

void Preview::DoPreview(const QFileInfo &fi)
{
    Clean();

    QString suffix = fi.completeSuffix();
    if(suffix == "html")
    {
        DoPreview_WebView(fi);
    }
    else if(suffix == "htm")
    {
        DoPreview_WebView(fi);
    }
    else if(suffix == "svg")
    {
        DoPreview_LabelImage(fi);
    }
    else if(suffix == "png")
    {
        DoPreview_LabelImage(fi);
    }
    else if(suffix == "bmp")
    {
        DoPreview_LabelImage(fi);
    }
    else if(suffix == "jpg")
    {
        DoPreview_LabelImage(fi);
    }
    else if(suffix == "gif")
    {
        DoPreview_LabelImage(fi);
    }
}

void Preview::DoPreview_WebView(const QFileInfo &fi)
{
    ui->webView->setVisible(true);
    ui->webView->load(QUrl(fi.canonicalFilePath()));
}

void Preview::DoPreview_LabelImage(const QFileInfo &fi)
{
    QPixmap pixmap;
    pixmap.load(fi.canonicalFilePath());
    //if()
    {
        ui->label->setVisible(true);
        ui->label->setPixmap(pixmap);
    }
}

void Preview::Clean()
{
    ui->label->setVisible(false);
    ui->webView->setVisible(false);
}

Preview::~Preview()
{
    delete ui;
}
