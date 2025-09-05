#ifndef LISTENER_H
#define LISTENER_H

#include <QtCore/QtCore>
#include <QtDBus/QtDBus>
#include "lfsapi.h"

class ListenerParent {
 public:
  virtual void onCmdComplete(qlonglong msg_id, qlonglong pointer) = 0;
  virtual void onInfoGot(qlonglong pointer) = 0;
  virtual void onExecuted(qlonglong pointer) = 0;
  virtual void eventArrived(qlonglong event_id, qlonglong pointer) = 0;
};

class ListenerParentProxy : public QTimer {
  Q_OBJECT

 public:
  ListenerParentProxy(ListenerParent* lp, qlonglong msg_id, qlonglong pointer);

 public slots:
  void trigger();

 private:
  ListenerParent* m_parent;
  qlonglong m_msgid;
  qlonglong m_pointer;
};

class DbusListener : public QDBusAbstractAdaptor {
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", LFS_MGR_DBUS_INTF_NAME)
 public:
  DbusListener(QObject* parent);

 public slots:
  void event_callback(qlonglong msg_id, qlonglong pointer);

 private:
  ListenerParent* m_parent;
};

#endif  // LISTENER_H
