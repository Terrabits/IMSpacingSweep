#include "FrequencyConversionTest.h"


// Project
#include "IntermodSettings.h"

// RsaToolbox
#include <General.h>
using namespace RsaToolbox;

// Qt
Q_DECLARE_METATYPE(IntermodSettings)


FrequencyConversionTest::FrequencyConversionTest(QObject *parent) : TestClass(parent)
{

}

FrequencyConversionTest::~FrequencyConversionTest()
{

}

// tests
void FrequencyConversionTest::lti_data() {
    QTest::addColumn<IntermodSettings>("settings");
    QTest::addColumn<QRowVector>("freq");

    // Case 1
    IntermodSettings settings1;
    settings1.setCenterFrequency  (  1, SiPrefix::Giga);
    settings1.setStartToneDistance( 10, SiPrefix::Mega);
    settings1.setStopToneDistance (100, SiPrefix::Mega);
    settings1.setPoints(10);

    QRowVector freq1;
    freq1 << 950000000.0
          << 955000000.0
          << 960000000.0
          << 965000000.0
          << 970000000.0
          << 975000000.0
          << 980000000.0
          << 985000000.0
          << 990000000.0
          << 995000000.0;
    QTest::newRow("case1") << settings1 << freq1;

    // Case 2
    IntermodSettings settings2;
    settings2.setCenterFrequency  ( 2, SiPrefix::Giga);
    settings2.setStartToneDistance( 1, SiPrefix::Mega);
    settings2.setStopToneDistance (10, SiPrefix::Mega);
    settings2.setPoints(21);

    QRowVector freq2;
    freq2 << 1995000000.0
          << 1995225000.0
          << 1995450000.0
          << 1995675000.0
          << 1995900000.0
          << 1996125000.0
          << 1996350000.0
          << 1996575000.0
          << 1996800000.0
          << 1997025000.0
          << 1997250000.0
          << 1997475000.0
          << 1997700000.0
          << 1997925000.0
          << 1998150000.0
          << 1998375000.0
          << 1998600000.0
          << 1998825000.0
          << 1999050000.0
          << 1999275000.0
          << 1999500000.0;
    QTest::newRow("case2") << settings2 << freq2;
}
void FrequencyConversionTest::lti() {
    QFETCH(IntermodSettings, settings);
    QFETCH(QRowVector , freq);

    FrequencyConversionGenerator fg(settings);
    QCOMPARE(fg.fbStart_Hz(), freq.first());
    QCOMPARE(fg.fbStop_Hz (), freq.last());
    QCOMPARE(fg.lowerInputFreq_Hz().first(), freq.first());
    QCOMPARE(fg.lowerInputFreq_Hz().last(),  freq.last());
    QCOMPARE(fg.lowerInputFreq_Hz(),         freq);
}

void FrequencyConversionTest::uti_data() {
    QTest::addColumn<IntermodSettings>("settings");
    QTest::addColumn<QRowVector>("freq");

    // Case 1
    IntermodSettings settings1;
    settings1.setCenterFrequency  (  1, SiPrefix::Giga);
    settings1.setStartToneDistance( 10, SiPrefix::Mega);
    settings1.setStopToneDistance (100, SiPrefix::Mega);
    settings1.setPoints(10);

    QRowVector freq1;
    freq1 << 1005000000.0
          << 1010000000.0
          << 1015000000.0
          << 1020000000.0
          << 1025000000.0
          << 1030000000.0
          << 1035000000.0
          << 1040000000.0
          << 1045000000.0
          << 1050000000.0;
    QTest::newRow("case1") << settings1 << freq1;

    // Case 2
    IntermodSettings settings2;
    settings2.setCenterFrequency  ( 2, SiPrefix::Giga);
    settings2.setStartToneDistance( 1, SiPrefix::Mega);
    settings2.setStopToneDistance (10, SiPrefix::Mega);
    settings2.setPoints(21);

    QRowVector freq2;
    freq2 << 2000500000.0
          << 2000725000.0
          << 2000950000.0
          << 2001175000.0
          << 2001400000.0
          << 2001625000.0
          << 2001850000.0
          << 2002075000.0
          << 2002300000.0
          << 2002525000.0
          << 2002750000.0
          << 2002975000.0
          << 2003200000.0
          << 2003425000.0
          << 2003650000.0
          << 2003875000.0
          << 2004100000.0
          << 2004325000.0
          << 2004550000.0
          << 2004775000.0
          << 2005000000.0;
    QTest::newRow("case2") << settings2 << freq2;
}
void FrequencyConversionTest::uti() {
    QFETCH(IntermodSettings, settings);
    QFETCH(QRowVector , freq);

    FrequencyConversionGenerator fg(settings);
    QCOMPARE(fg.upperInputFreq_Hz().size(),  freq.size());
    QCOMPARE(fg.upperInputFreq_Hz().first(), freq.first());
    QCOMPARE(fg.upperInputFreq_Hz().last(),  freq.last());
    QCOMPARE(fg.upperInputFreq_Hz(),         freq);
}

void FrequencyConversionTest::iml_data() {
    QTest::addColumn<IntermodSettings>("settings");
    QTest::addColumn<uint>("order");
    QTest::addColumn<QRowVector>("freq");

    // Case 1
    IntermodSettings settings1;
    settings1.setCenterFrequency  (  1, SiPrefix::Giga);
    settings1.setStartToneDistance( 10, SiPrefix::Mega);
    settings1.setStopToneDistance (100, SiPrefix::Mega);
    settings1.setPoints(10);

    // n = 3
    QRowVector freq1_3;
    freq1_3 << 850000000.0
            << 865000000.0
            << 880000000.0
            << 895000000.0
            << 910000000.0
            << 925000000.0
            << 940000000.0
            << 955000000.0
            << 970000000.0
            << 985000000.0;
    QTest::newRow("case1n3") << settings1 << uint(3) << freq1_3;

    // n = 5
    QRowVector freq1_5;
    freq1_5 << 750000000.0
            << 775000000.0
            << 800000000.0
            << 825000000.0
            << 850000000.0
            << 875000000.0
            << 900000000.0
            << 925000000.0
            << 950000000.0
            << 975000000.0;
    QTest::newRow("case1n5") << settings1 << uint(5) << freq1_5;

    // n = 7
    QRowVector freq1_7;
    freq1_7 << 650000000.0
            << 685000000.0
            << 720000000.0
            << 755000000.0
            << 790000000.0
            << 825000000.0
            << 860000000.0
            << 895000000.0
            << 930000000.0
            << 965000000.0;
    QTest::newRow("case1n7") << settings1 << uint(7) << freq1_7;

    // n = 9
    QRowVector freq1_9;
    freq1_9 << 550000000.0
            << 595000000.0
            << 640000000.0
            << 685000000.0
            << 730000000.0
            << 775000000.0
            << 820000000.0
            << 865000000.0
            << 910000000.0
            << 955000000.0;
    QTest::newRow("case1n9") << settings1 << uint(9) << freq1_9;

    // Case 2
    IntermodSettings settings2;
    settings2.setCenterFrequency  ( 2, SiPrefix::Giga);
    settings2.setStartToneDistance( 1, SiPrefix::Mega);
    settings2.setStopToneDistance (10, SiPrefix::Mega);
    settings2.setPoints(21);

    // n = 3
    QRowVector freq2;
    freq2 << 1985000000.0
          << 1985675000.0
          << 1986350000.0
          << 1987025000.0
          << 1987700000.0
          << 1988375000.0
          << 1989050000.0
          << 1989725000.0
          << 1990400000.0
          << 1991075000.0
          << 1991750000.0
          << 1992425000.0
          << 1993100000.0
          << 1993775000.0
          << 1994450000.0
          << 1995125000.0
          << 1995800000.0
          << 1996475000.0
          << 1997150000.0
          << 1997825000.0
          << 1998500000.0;
    QTest::newRow("case2") << settings2 << uint(3) << freq2;
}
void FrequencyConversionTest::iml() {
    QFETCH(IntermodSettings, settings);
    QFETCH(uint, order);
    QFETCH(QRowVector, freq);

    FrequencyConversionGenerator fg(settings);
    QCOMPARE(fg.lowerOutputFreq_Hz(order).size(),  freq.size());
    QCOMPARE(fg.lowerOutputFreq_Hz(order).first(), freq.first());
    QCOMPARE(fg.lowerOutputFreq_Hz(order).last(),  freq.last());
    QCOMPARE(fg.lowerOutputFreq_Hz(order), freq);
}

void FrequencyConversionTest::imu_data() {
    // CASE 2
    //   n = 3
//    freq_Hz << 2015000000.0
//            << 2014325000.0
//            << 2013650000.0
//            << 2012975000.0
//            << 2012300000.0
//            << 2011625000.0
//            << 2010950000.0
//            << 2010275000.0
//            << 2009600000.0
//            << 2008925000.0
//            << 2008250000.0
//            << 2007575000.0
//            << 2006900000.0
//            << 2006225000.0
//            << 2005550000.0
//            << 2004875000.0
//            << 2004200000.0
//            << 2003525000.0
//            << 2002850000.0
//            << 2002175000.0
//            << 2001500000.0;
}
void FrequencyConversionTest::imu() {

}

// private
void FrequencyConversionTest::createTestCaseData() {
    //  CASE 1:
    //  center frequency = 1 GHz
    //  tone distance    = [10 MHz ... 100 MHz]
    //  points           = 10
    //
    //  | N | Side | Start     | Stop      |
    //  |---|------|-----------|-----------|
    //  | 1 | L    | 0.950 GHz | 0.995 GHz |
    //  | 3 | L    | 0.850 GHz | 0.985 GHz |
    //  | 5 | L    | 0.750 GHz | 0.975 GHz |
    //  | 7 | L    | 0.650 GHz | 0.965 GHz |
    //  | 9 | L    | 0.550 GHz | 0.955 GHz |
    //  | 1 | U    | 1.050 GHz | 1.005 GHz |
    //  | 3 | U    | 1.150 GHz | 1.015 GHz |
    //  | 5 | U    | 1.250 GHz | 1.025 GHz |
    //  | 7 | U    | 1.350 GHz | 1.035 GHz |
    //  | 9 | U    | 1.450 GHz | 1.045 GHz |
    //
    IntermodSettings case1;
    case1.setCenterFrequency  (  1, SiPrefix::Giga);
    case1.setStartToneDistance( 10, SiPrefix::Mega);
    case1.setStopToneDistance (100, SiPrefix::Mega);
    case1.setPoints(10);

    //  CASE 2:
    //  center frequency = 2 GHz
    //  tone distance    = [1 MHz ... 10 MHz]
    //  points           = 21
    //
    //  | N | Side | Start     | Stop      |
    //  |---|------|-----------|-----------|
    //  | 1 | L    | 0.950 GHz | 0.995 GHz |
    //  | 3 | L    | 0.850 GHz | 0.985 GHz |
    //  | 5 | L    | 0.750 GHz | 0.975 GHz |
    //  | 7 | L    | 0.650 GHz | 0.965 GHz |
    //  | 9 | L    | 0.550 GHz | 0.955 GHz |
    //  | 1 | U    | 1.050 GHz | 1.005 GHz |
    //  | 3 | U    | 1.150 GHz | 1.015 GHz |
    //  | 5 | U    | 1.250 GHz | 1.025 GHz |
    //  | 7 | U    | 1.350 GHz | 1.035 GHz |
    //  | 9 | U    | 1.450 GHz | 1.045 GHz |
    //
    IntermodSettings case2;
    case2.setCenterFrequency  ( 2, SiPrefix::Giga);
    case2.setStartToneDistance( 1, SiPrefix::Mega);
    case2.setStopToneDistance (10, SiPrefix::Mega);
    case2.setPoints(21);
}
