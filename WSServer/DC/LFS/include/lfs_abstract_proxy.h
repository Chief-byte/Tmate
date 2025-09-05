#ifndef LFS_ABSTRACT_PROXY_H__
#define LFS_ABSTRACT_PROXY_H__

#include <string>
#include <QQuickItem>
#include <QSettings>

#include "lfsapi.h"
#include "listener.h"

class LFSAbstractProxy : public QQuickItem, public ListenerParent
{
    Q_OBJECT
    Q_PROPERTY(QString svcName READ svcName WRITE setSvcName)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)

public:
    LFSAbstractProxy(const char* dbus_obj_name, const char* group_name, QQuickItem *parent = 0);
    virtual ~LFSAbstractProxy();

    QString svcName() const {
        return m_svc_name;
    }

    void setSvcName(const QString & name) {
        if (name == m_svc_name)
            return;
        m_svc_name = name;
        m_settings->beginGroup(m_group_name);
        m_settings->setValue("service", name);
        m_settings->endGroup();
    }

    int timeout() const {
        return m_timeout;
    }

    void setTimeout(int to) {
        if (to == m_timeout)
            return;
        m_timeout = to;
        m_settings->beginGroup(m_group_name);
        m_settings->setValue("timeout", to);
        m_settings->endGroup();
    }

    virtual void onCmdComplete(qlonglong msg_id, qlonglong pointer);

    Q_INVOKABLE bool saveFile(const QString& filename, const QString& content);
    Q_INVOKABLE bool open(const QString& app_id);
    Q_INVOKABLE void close();
    Q_INVOKABLE void lock();
    Q_INVOKABLE void unlock();
    Q_INVOKABLE void lfsRegister();
    Q_INVOKABLE void deregister();
    Q_INVOKABLE void cancel();
    Q_INVOKABLE void getInfoNoArg(int category);
    Q_INVOKABLE void executeNoArg(int cmd);
    Q_INVOKABLE int startUp(int version_required);
    Q_INVOKABLE int cleanUp();

signals:
    void newMsg(const QString& msg);
    void cmdComplete(qlonglong msgid, long result);

public slots:

protected:
    void appendText(std::string msg);

protected:
    DbusListener* m_listener;
    QString m_svc_name;
    int m_timeout;
    HSERVICE m_service;
    REQUESTID m_open_reqid, m_last_reqid;
    char* m_dbus_obj_name;
    char* m_group_name;
    QSettings* m_settings;
};

#endif // LFS_ABSTRACT_PROXY_H__
