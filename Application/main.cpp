

//Project
#include "CalibrateWidget.h"
#include "IntermodError.h"
#include "IntermodWidget.h"
#include "Settings.h"
#include "TracesWidget.h"

// RsaToolbox
#include <About.h>
#include <GenericBus.h>
#include <Keys.h>
#include <Log.h>
#include <Vna.h>
#include <Wizard.h>
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QMessageBox>

// Functions
bool isAboutMenu(int argc, char *argv[]);
bool isRohdeSchwarzVna(Vna &vna);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // --about flag?
    if (isAboutMenu(argc, argv))
        return 0;

    // Vna connection, log
    Vna vna(CONNECTION_TYPE, ADDRESS);
    Log log(LOG_FILENAME, APP_NAME, APP_VERSION);
    log.printHeader();
    vna.useLog(&log);
    if (!isRohdeSchwarzVna(vna))
        return 0;

    // Keys / saved settings
    Keys keys(KEY_PATH);

    // Title
    QString title = "%1 %2";
    title = title.arg(APP_NAME);
    title = title.arg(APP_VERSION);

    // Wizard
    Wizard wizard;
    wizard.setWindowTitle(title);
    wizard.hideBreadcrumbs();
    wizard.setRestartOnCancel(false);

    // Settings page
    IntermodWidget *settings = new IntermodWidget(&vna, &keys);
    settings->setNextIndex(1);
    QObject::connect(settings, SIGNAL(error(IntermodError)),
                     &wizard,  SLOT(shake()));
    QObject::connect(settings, SIGNAL(errorMessage(QString)),
                     &wizard,  SLOT(shake()));
    wizard.addPage(settings);

    // Traces page
    TracesWidget *traces = new TracesWidget(&vna, &keys);
    traces->setNextIndex(2);
    QObject::connect(settings, SIGNAL(validatedInput(IntermodSettings)),
                     traces,   SLOT(setSettings(IntermodSettings)));
    QObject::connect(traces,   SIGNAL(error(IntermodError)),
                     &wizard,  SLOT(shake()));
    QObject::connect(traces,   SIGNAL(errorMessage(QString)),
                     &wizard,  SLOT(shake()));
    wizard.addPage(traces);

    // Calibration page
    CalibrateWidget *cal = new CalibrateWidget(&vna);
    // cal->setNext(3);
    cal->setFinalPage(true);
    QObject::connect(settings, SIGNAL(validatedInput(IntermodSettings)),
                     cal,      SLOT(setSettings(IntermodSettings)));
    QObject::connect(traces,   SIGNAL(validatedInput(QList<IntermodTrace>)),
                     cal,      SLOT(setTraces(QList<IntermodTrace>)));
    wizard.addPage(cal);

    // Process traces
    // ProcessTracesWidget *process = new ProcessTracesWidget(&vna);
    // process->setFinal(true);
    // QObject::connect(settings, SIGNAL(validatedInput(IntermodSettings)),
    //                  process,  SLOT(setSettings(IntermodSettings)));
    // QObject::connect(traces,   SIGNAL(validatedInput(QList<IntermodTrace>)),
    //                  process,  SLOT(setTraces(QList<IntermodTrace>)));
    // wizard.addPage(cal);

    // Start event loop
    wizard.show();
    int result = a.exec();

    // Save keys?
    IntermodError e;
    if (settings->isValidInput(e))
        settings->saveInput();
    if (traces->isValidInput(e))
        traces->saveInput();

    return result;
}

// Functions
bool isAboutMenu(int argc, char *argv[]) {
    if (argc != 2)
        return false;

    QString arg(argv[1]);
    arg = arg.trimmed().toUpper();
    if (arg == "-ABOUT" || arg == "--ABOUT") {
        Q_INIT_RESOURCE(AboutResources);
        About about;
        about.setAppName(APP_NAME);
        about.setVersion(APP_VERSION);
        about.setDescription(APP_DESCRIPTION);
        about.setContactInfo(CONTACT_INFO);
        about.exec();
        return true;
    }

    return false;
}
bool isRohdeSchwarzVna(Vna &vna) {
    if (!vna.isConnected() || vna.idString().isEmpty()) {
        QString msg = "Could not connect to instrument.\n"
                      "Please check your VISA installation and\n"
                      "run this application on the instrument.";
        QMessageBox::critical(NULL,
                              APP_NAME,
                              msg);
        vna.print(msg);
        return false;
    }
    vna.settings().setEmulationOff();
    if (!vna.properties().isKnownModel()) {
        QString msg = "Instrument not recognized.\n"
                      "Please use %1 with a Rohde & Schwarz VNA\n"
                      "with emulation mode turned off.";
        msg = msg.arg(APP_NAME);
        QMessageBox::critical(NULL,
                              APP_NAME,
                              msg);
        vna.print(msg);
        return false;
    }

    return true;
}
