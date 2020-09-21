#include <QApplication>
#include <QMainWindow>

#include <QDebug>
#include <QFile>
#include <QLabel>
#include <QVBoxLayout>

#include<purchase.h>

enum RetCode {
    RetCodeAuthSuccess,
    RetCodeAuthFailed,
    RetCodeKeyInvalid,
    RetCodeOffline,
    RetCodeOfflineExpired,
    RetCodeUserNotLogin
};

static auto publicKey = R"(-----BEGIN RSA PUBLIC KEY-----
MIIBCgKCAQEAwFp6Hobh7bvF3dNWXzKi4NWREp0vzzpUChDTx7li5gJugdT8UDGY
FUFDct95S8ZpNpL+guRNspRuUoaAshEWJ3kbKglpVNevL4GTSg0e2S4ZRb+o8g9u
W/BnDb+rUbFSjmgFExEfNOps1yLyF+QYQwFOdzSHNM4gANc3YIG0FVpc6JU57h0j
SgzJOFT1mg8U/Hj18U+OumkldJaeISllbkCpHzTz4JJBp49rTc5V+/D5tFddxkRW
YnLqWL1dAKUW+rjMRL+08nOyGV7G31t+/n+IFcPhk6vcukrqHgOQplmH7fByoQPX
iMWba/V/2NG6YNi3MML74vDO4SAOtYdYRQIDAQAB
-----END RSA PUBLIC KEY-----
)";

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QLabel *retLabel = new QLabel();
    QLabel *txtLabel = new QLabel();

    QFile publicKeyFile(qEnvironmentVariable("COM_DEEPIN_DEMO_PUBLICKEY"));
    if (publicKeyFile.open(QIODevice::ReadOnly)) {
        publicKey = publicKeyFile.readAll();
    }

    int ret =  verifyAuth("com.deepin.demo", publicKey);
    qDebug() << "-- verify Auth get code: " << ret;
    retLabel->setText(QString("retCode: ") + QString::number(ret));

    if (ret == RetCodeUserNotLogin) {
        qDebug() << "-- check purchased user not login, please login !!";
        txtLabel->setText("msg: check purchased user not login, please login !!");
        login();
    }

    if (ret == RetCodeOfflineExpired) {
        qDebug() << "-- check purchased offline and local auth expire !!";
        txtLabel->setText("msg: check purchased offline and local auth expire !!");
    }

    if (ret == RetCodeOffline) {
        qDebug() << "-- check purchased failed, offline error !!";
        txtLabel->setText("msg: check purchased failed, offline error !!");
    }

    if (ret == RetCodeKeyInvalid) {
        qDebug() << "-- check purchased package invalid !!";
        txtLabel->setText("msg: check purchased package invalid !!");
    }

    if (ret == RetCodeAuthFailed) {
        qDebug() << "-- check purchased failed, please purchased !!";
        int ret = purchase("com.deepin.demo");
        if (0 != ret) {
            txtLabel->setText("msg: check purchased failed, call purchase interface error !!");
        }
        txtLabel->setText("msg: check purchased failed, called purchase interface !!");
    }

    // RetCodeAuthSuccess
    if (ret == RetCodeAuthSuccess){
        txtLabel->setText("msg: check purchased success !!");
    }

    QMainWindow w;
    QVBoxLayout *layout = new QVBoxLayout;
    QWidget *centWg = new QWidget();
    layout->addStretch();
    layout->addWidget(retLabel);
    layout->addWidget(txtLabel);
    centWg->setLayout(layout);
    layout->addStretch();

    w.setCentralWidget(centWg);
    w.show();
    w.resize(450, 300);

    return app.exec();
}
