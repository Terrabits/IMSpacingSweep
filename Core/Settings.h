#ifndef SETTINGS_H
#define SETTINGS_H


// RsaToolbox
#include <Definitions.h>
#include <General.h>
#include <GenericBus.h>


// Application settings
const QString APP_NAME            = "R&S IM Spacing Sweep";
const QString APP_VERSION         = "1.3";
const QString MANUFACTURER_FOLDER = "Rohde-Schwarz";
const QString APP_FOLDER          = "IM Spacing Sweep";
const QString APP_DESCRIPTION     = "Measure IM products vs tone spacing for a given center frequency";
const QString CONTACT_INFO        = "<html><head/><body><p>Nick Lalic<br/>VNA Software Developer<br/>Half Moon Bay, CA USA<br/>+1 424 200 2846<br/>nick.lalic@rsa.rohde-schwarz.com<br/><a href=\"http://vna.rs-us.net\"><span style=\"text-decoration: underline; color:#0000ff;\">http://vna.rs-us.net</span></a></p></body></html>";

#ifdef DEBUG_MODE
// Debug program data
const QDir    dataDir(SOURCE_DIR);
const QString LOG_FILENAME = dataDir.filePath("_Debug/Log.txt");
const QString KEY_PATH     = dataDir.filePath("_Debug/Keys");

// Debug Connection settings
const RsaToolbox::ConnectionType CONNECTION_TYPE = RsaToolbox::ConnectionType::VisaTcpSocketConnection;
const QString                    ADDRESS         = "127.0.0.1::5025";

#else
// Release program data
const QDir    dataDir(RsaToolbox::GetAppDataPath(MANUFACTURER_FOLDER, APP_FOLDER));
const QString LOG_FILENAME = dataDir.filePath("R&S IM Spacing Sweep Log.txt");
const QString KEY_PATH     = dataDir.filePath("Settings");

// Release Connection settings
const RsaToolbox::ConnectionType CONNECTION_TYPE = RsaToolbox::ConnectionType::VisaTcpSocketConnection;
const QString                    ADDRESS         = "127.0.0.1::5025";
#endif

// Keys
//const QString MY_KEY = "MY_KEY";

#endif // SETTINGS_H

