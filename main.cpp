/* * * * *
 * Название: hello-hw-status - пример взаимодейтсвия с аппаратурой через брокер
 * Версия: 0.0.1
 * Описание: производит запрос состояния контроллеров посредством брокера
 * Программист разработчик: Дарьин М.В.
 * Программист сопровождения:
 * Дата создания: 11.06.2014
 * Дата последнего изменения:
 * Организация: ЗАО "ОКБ "ИКАР"
 * Лицензия: "AS-IS" "NO WARRENTY"
 * Контакты:
 * почта: 
 * адрес: 
 * 
 * 2014
 * 
 * * */ 
#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <hardware.hh>
#include "widget.h"
#include "hwstatusrequester.h"


//NOTE: see also http://qt-way-notes.blogspot.ru/2010/07/tree-model-qml.html
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList <QByteArray> all_args;
    QString initref = QString("HWBroker=corbaloc::localhost:25000/HWBroker");
    all_args.append("-ORBInitRef");
    all_args.append(initref.toLatin1());

    int cargc = all_args.count();
    char **cargv = new char*[cargc];
    for (int i = 0; i < cargc; ++i) {
        std::cout << all_args[i].data();
        cargv[i] = all_args[i].data();
    if (i % 2)
        std::cout << (i > 2 ? "\"\n\t" : " ");
    else
        std::cout << (i > 3 ? "=\"" : " ");
    }
    std::cout << std::endl;

    CORBA::ORB_var orb = CORBA::ORB_init(cargc, cargv);
    CORBA::Object_var obj;

    HWStatusRequester *hwsr = new HWStatusRequester;

//    Widget w;
//    w.show();



    try {
        obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
//        PortableServer::ObjectId_var logic_var = poa->activate_object(hwsr);  //hwsr itself is not a CORBA object
        PortableServer::POAManager_var pman = poa->the_POAManager();
        pman->activate();

        //находим диспетчер
        CORBA::Object_var obj = orb->resolve_initial_references("HWBroker");
        icore::HWBroker_var hwbroker =
                icore::HWBroker::_narrow(obj);
        hwsr->setHWBroker(hwbroker);   //передаем диспетчер в наш объект
//        hwbroker->registerGenericReplyConsumer(consumer->_this());  //регистрируемся в диспетчере
    }
    catch (CORBA::NO_RESOURCES&) {
        std::cerr << "Caught CORBA::NO_RESOURCES exception.\n\t You must configure omniORB "
                << "with the location of the naming service." << std::endl;
    }
    catch(CORBA::SystemException& ex) {
        std::cerr << "Caught CORBA::SystemException: " << ex._name() << std::endl;
    }
    catch(CORBA::Exception& ex) {
        std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
    }
    catch(omniORB::fatalException& fe) {
        std::cerr << "Caught omniORB::fatalException:" << std::endl;
        std::cerr << " file: " << fe.file() << std::endl;
        std::cerr << " line: " << fe.line() << std::endl;
        std::cerr << " mesg: " << fe.errmsg() << std::endl;
    }
    catch(...) {
        std::cerr << "Caught unknown exception." << std::endl;
    }
    
    return a.exec();
} // eof main
