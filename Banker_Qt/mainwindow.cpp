#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);  //无边框化
    setFixedSize(this->width(),this->height());

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame->setGraphicsEffect(effect);

    ui->widget->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect_2 = new QGraphicsDropShadowEffect(this);
    effect_2->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect_2->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect_2->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame_2->setGraphicsEffect(effect_2);

    ui->widget_2->setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *effect_3 = new QGraphicsDropShadowEffect(this);
    effect_3->setOffset(0, 0);          //设置向哪个方向产生阴影效果(dx,dy)，特别地，(0,0)代表向四周发散
    effect_3->setColor(Qt::gray);       //设置阴影颜色，也可以setColor(QColor(220,220,220))
    effect_3->setBlurRadius(20);        //设定阴影的模糊半径，数值越大越模糊
    ui->frame_3->setGraphicsEffect(effect_3);

    QRegExp regExp2("[0-9]{1,4}");   //正则要求输入必须为正整数
    QRegExpValidator *pRegExpValidator2 = new QRegExpValidator(regExp2,this);
    ui->lineEdit->setValidator(pRegExpValidator2);
    ui->lineEdit_2->setValidator(pRegExpValidator2);

    ui->widget->hide();
    ui->widget_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) //窗口移动事件
{
    m_pressed = true;
    m_movePos = event->globalPos() - pos();

    return QMainWindow::mousePressEvent(event);
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_pressed
        && (event->buttons()== Qt::LeftButton)
        && (event->globalPos() - m_movePos).manhattanLength() > QApplication::startDragDistance())
    {
        QPoint movePos = event->globalPos() - m_movePos;
        this->move(movePos);
        m_movePos = event->globalPos() - pos();
    }

    return QMainWindow::mouseMoveEvent(event);
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;

    return QMainWindow::mouseReleaseEvent(event);
}


void MainWindow::on_pushButton_2_clicked()  //关闭系统
{
    close();
}

void MainWindow::on_pushButton_3_clicked()  //最小化
{
    showMinimized();
}

void MainWindow::on_pushButton_clicked()   //根据输入的资源数和用户数动态建表
{
    if(ui->lineEdit->text().toInt()<max && ui->lineEdit_2->text().toInt()<max
            && ui->lineEdit->text()!=nullptr && ui->lineEdit_2->text()!=nullptr){
        resc_num=ui->lineEdit->text().toInt();
        client_num=ui->lineEdit_2->text().toInt();

        ui->tableWidget->setColumnCount(resc_num);
        ui->tableWidget->setRowCount(client_num);
        QStringList HStrList;       //初始化项名
        for(int i=1;i<=resc_num;i++){
            HStrList.push_back(QString("资源"+QString::number(i)));
        }
        ui->tableWidget->setHorizontalHeaderLabels(HStrList);
        QStringList VStrList;
        for(int i=1;i<=client_num;i++){
            VStrList.push_back(QString("用户"+QString::number(i)));
        }
        ui->tableWidget->setVerticalHeaderLabels(VStrList);
        ui->tableWidget->resizeRowsToContents();
        ui->tableWidget->resizeColumnsToContents();

        ui->tableWidget_2->setColumnCount(resc_num);
        ui->tableWidget_2->setRowCount(client_num);
        ui->tableWidget_2->setHorizontalHeaderLabels(HStrList);
        ui->tableWidget_2->setVerticalHeaderLabels(VStrList);
        ui->tableWidget_2->resizeRowsToContents();
        ui->tableWidget_2->resizeColumnsToContents();

        ui->tableWidget_3->setColumnCount(resc_num);
        ui->tableWidget_3->setRowCount(1);
        ui->tableWidget_3->setHorizontalHeaderLabels(HStrList);
        QStringList mStrList;
        mStrList.push_back(QString("总数"));
        ui->tableWidget_3->setVerticalHeaderLabels(mStrList);
        ui->tableWidget_3->resizeColumnsToContents();

        ui->tableWidget_4->setColumnCount(resc_num);
        ui->tableWidget_4->setRowCount(1);
        ui->tableWidget_4->setHorizontalHeaderLabels(HStrList);
        QStringList nStrList;
        nStrList.push_back(QString("请求量"));
        ui->tableWidget_4->setVerticalHeaderLabels(nStrList);
        ui->tableWidget_4->resizeColumnsToContents();

        ui->comboBox->clear();
        for(int i=1;i<=client_num;i++){
            ui->comboBox->addItem(QString::number(i));
        }
    }
    else if(ui->lineEdit->text()==nullptr || ui->lineEdit_2->text()==nullptr)QMessageBox::warning(this,"输入不能为空","请输入资源数和用户数");
    else QMessageBox::warning(this,"输入数字过大","输入必须小于30");
}

void MainWindow::initialize(){    //对输入的各项数据存储
    for (int i = 0; i < client_num; i++)
    {
        for (int j = 0; j < resc_num; j++)
        {
            Alloc[i][j]=ui->tableWidget->item(i,j)->text().toInt();
        }
    }
    for (int i = 0; i < client_num; i++)
    {
        for (int j = 0; j < resc_num; j++)
        {
            Max[i][j]=ui->tableWidget_2->item(i,j)->text().toInt();
        }
    }
    for (int i = 0; i < resc_num; i++)
    {
        resc[i]=ui->tableWidget_3->item(0,i)->text().toInt();
    }
    for (int i = 0; i < client_num; i++)
    {
        for (int j = 0; j < resc_num; j++)
        {
            Need[i][j] = Max[i][j] - Alloc[i][j];
        }
    }
    for (int j = 0; j < resc_num; j++)
    {
        Avail[j] = resc[j];//可用资源数
        for (int i = 0; i < client_num; i++)
        {
            Avail[j] -= Alloc[i][j]; //分配完之后剩下的资源总数
        }  
    }
    for (int i = 0; i < client_num; i++)   //检测有已经分配完的进程则回收资源
    {
        bool flag=true;
        for (int j = 0; j < resc_num; j++)
        {
            if(Need[i][j]!=0){
                flag=false;
            }
        }
        if(flag){
            for(int j=0; j<resc_num; j++){
                Avail[j]+=Alloc[i][j];
            }
        }
    }
}

int MainWindow::checktable(){    //是否有不符合要求的数据
    for(int i=0;i<client_num;i++){
        for(int j=0;j<resc_num;j++){
             if(ui->tableWidget->item(i,j)==nullptr)return 1;
             if(ui->tableWidget_2->item(i,j)==nullptr)return 1;
             QString nu=ui->tableWidget->item(i,j)->text();
             if(nu.toInt()<0||nu.toInt()>max)return 2;
             QString mu=ui->tableWidget_2->item(i,j)->text();
             if(mu.toInt()<0||mu.toInt()>max)return 2;
        }
    }
    for(int i=0;i<resc_num;i++){
        if(ui->tableWidget->item(0,i)==nullptr)return 1;
        QString ku=ui->tableWidget_3->item(0,i)->text();
        if(ku.toInt()<0||ku.toInt()>30)return 2;
    }
    return 0;
}

bool MainWindow::SecureCheck()    //初始化 判断函数 需要的各种数组
{  
    sum=0;
    ui->textBrowser->clear();
    bool security[client_num];//security[i]表示对用户i的分配是否安全
    memset(security,false,sizeof (security));
    int temp[resc_num]; //避免检测时对Available数组进行修改
    for (int i = 0; i < resc_num; i++)
    {
        temp[i] = Avail[i];
    }
    int k = 0;
    SecureDFS(security,temp,k);
    if(sum==0)return false;
    else return true;
}
void MainWindow::SecureDFS(bool *security,int *temp,int k)   //深度优先递归检测死锁并打印安全系列
{
    if(k == client_num){     //找到了一种安全性序列，打印输出(递归出口)
        if(sum==0)ui->widget->show();
        sum++;
        QString scq=ui->textBrowser->toPlainText();
        if(scq!=nullptr)scq+="\n";
        scq+=QString::number(ans[0]+1);
        for (int i = 1; i < k; i++)
        {
            scq+="->"+QString::number(ans[i]+1);
        }
        ui->textBrowser->setText(scq);
        return;
    }

    int i;   //死锁判断
    for(i=0; i<client_num; i++){
        if(!security[i])
        {
            int j;
            bool client_ifsec = true;
            for(j=0; j<resc_num; j++)
            {
                if(Need[i][j] > temp[j])
                {
                    client_ifsec = false;        //该进程不安全
                }
            }
            if(client_ifsec){        //第i个进程满足要求，暂时放入安全性队列
                for(j=0; j<resc_num; j++)
                {
                    temp[j] += Alloc[i][j];    //归还资源
                }
                security[i] = true;
                ans.push_back(i);
                SecureDFS(security,temp,k+1);     //递归搜索下一层
                ans.pop_back();       //回溯，将第i个进程所做的改变恢复
                for(j=0; j<resc_num; j++)
                {
                    temp[j] -= Alloc[i][j];
                }
                security[i] = false;
            }
        }
    }
}

void MainWindow::on_pushButton_4_clicked()  //生成安全序列
{
    if(ui->tableWidget->rowCount()>0&&ui->tableWidget->columnCount()>0){
        int ifok;
        ifok=checktable();
        if(ifok==0){
            initialize();
            bool flag=true;
            for(int i=0;i<client_num;i++){
                for(int j=0;j<resc_num;j++){
                    if(Alloc[i][j]!=Max[i][j])flag=false;
                }
            }
            if(flag){
                QMessageBox::information(this,"提示","资源已经全部安全分配给各进程");
                return;
            }
            if(!SecureCheck())QMessageBox::critical(this,"不安全","当前系统状态不安全！");
        }
        else if(ifok==1)QMessageBox::warning(this,"操作失败","存在输入为空的数据");
        else if(ifok==2)QMessageBox::warning(this,"操作失败","数据输入必须为正整数且小于30");
    }
    else QMessageBox::critical(this,"注意","请先输入资源数和用户数，然后点击开始分配。");
}

void MainWindow::RescRequest(){  //请求资源
    ui->widget_2->show();
    ui->comboBox->showPopup();
}

void MainWindow::on_pushButton_5_clicked()  //资源请求
{
    if(ui->tableWidget->rowCount()>0&&ui->tableWidget->columnCount()>0){
        int ifok;
        ifok=checktable();
        if(ifok==0){
            initialize();
            bool flag=true;
            for(int i=0;i<client_num;i++){
                for(int j=0;j<resc_num;j++){
                    if(Alloc[i][j]!=Max[i][j])flag=false;
                }
            }
            if(flag){
                QMessageBox::information(this,"提示","资源已经全部安全分配给各进程");
                return;
            }
            if(SecureCheck()){
                ui->widget->hide();
                RescRequest();
            }
            else QMessageBox::critical(this,"不安全","当前系统状态不安全，无法进行资源的分配！");
        }
        else if(ifok==1)QMessageBox::warning(this,"操作失败","存在输入为空的数据");
        else if(ifok==2)QMessageBox::warning(this,"操作失败","数据输入必须为正整数且小于30");
    }
    else QMessageBox::critical(this,"注意","请先输入资源数和用户数，然后点击开始分配。");
}

void MainWindow::on_pushButton_6_clicked()  //关闭安全序列框
{
    ui->widget->hide();
    sum=0;
}

bool MainWindow::checkquest(){
    int Request[resc_num];
    QString clientstr=ui->comboBox->currentText();
    int client=clientstr.toInt()-1;
    for (int j = 0; j < resc_num; j++)
    {
        Request[j]=ui->tableWidget_4->item(0,j)->text().toInt();
    }
        //不能多于最大请求
    for (int j = 0; j < resc_num; j++)
    {
        if (Request[j] + Alloc[client][j] > Max[client][j]){
            QMessageBox::warning(this,"失败","用户"+clientstr+"对资源"+QString::number(j+1)+"的请求超出需求的最大值");
            return false;
        }
    }
    for (int j = 0; j < resc_num; j++)
    {
        if (Request[j] > Avail[j]){
            QMessageBox::warning(this,"失败","系统没有足够的资源"+QString::number(j+1)+"提供给用户"+clientstr);
            return false;
        }
    }
    //尝试分配
    for (int j = 0; j < resc_num; j++)
    {
        Alloc[client][j] += Request[j];
        Need[client][j] -= Request[j];
    }
    for (int j = 0; j < resc_num; j++)
    {
        Avail[j] -= Request[j];
    }
    if (!SecureCheck()) {//如果系统不处于安全状态。则本次分配作废，恢复原来的资源分配状态
        QMessageBox::critical(this,"错误","该分配会导致不安全的状态。");
        for (int j = 0; j < resc_num; j++)
        {
            Alloc[client][j] -= Request[j];
            Need[client][j] += Request[j];
        }
        for (int j = 0; j < resc_num; j++)
            Avail[j] += Request[j];
        return false;
    }
    for(int i=0;i<resc_num;i++){
        ui->tableWidget->item(client,i)->setText(QString::number(Alloc[client][i]));
    }
    return true;
}

void MainWindow::on_pushButton_7_clicked()
{
    for(int i=0;i<resc_num;i++){
        if(ui->tableWidget_4->item(0,i)==nullptr){
            QMessageBox::warning(this,"错误","有数据为空。");
            return;
        }
    }
    if(checkquest()){
        ui->widget->hide();
        QMessageBox::about(this,"成功","请求资源成功！");
        ui->widget_2->hide();
        sum=0;
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->widget_2->hide();
    sum=0;
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->widget->hide();
    sum=0;
}
