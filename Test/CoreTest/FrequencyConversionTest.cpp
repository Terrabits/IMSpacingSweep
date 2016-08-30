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
    QRowVector freq2_3;
    freq2_3 << 1985000000.0
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
    QTest::newRow("case2n3") << settings2 << uint(3) << freq2_3;

    // n = 5
    QRowVector freq2_5;
    freq2_5 << 1975000000.0
            << 1976125000.0
            << 1977250000.0
            << 1978375000.0
            << 1979500000.0
            << 1980625000.0
            << 1981750000.0
            << 1982875000.0
            << 1984000000.0
            << 1985125000.0
            << 1986250000.0
            << 1987375000.0
            << 1988500000.0
            << 1989625000.0
            << 1990750000.0
            << 1991875000.0
            << 1993000000.0
            << 1994125000.0
            << 1995250000.0
            << 1996375000.0
            << 1997500000.0;
    QTest::newRow("case2n5") << settings2 << uint(5) << freq2_5;

    // n = 7
    QRowVector freq2_7;
    freq2_7 << 1965000000.0
            << 1966575000.0
            << 1968150000.0
            << 1969725000.0
            << 1971300000.0
            << 1972875000.0
            << 1974450000.0
            << 1976025000.0
            << 1977600000.0
            << 1979175000.0
            << 1980750000.0
            << 1982325000.0
            << 1983900000.0
            << 1985475000.0
            << 1987050000.0
            << 1988625000.0
            << 1990200000.0
            << 1991775000.0
            << 1993350000.0
            << 1994925000.0
            << 1996500000.0;
    QTest::newRow("case2n7") << settings2 << uint(7) << freq2_7;

    // n = 9
    QRowVector freq2_9;
    freq2_9 << 1955000000.0
            << 1957025000.0
            << 1959050000.0
            << 1961075000.0
            << 1963100000.0
            << 1965125000.0
            << 1967150000.0
            << 1969175000.0
            << 1971200000.0
            << 1973225000.0
            << 1975250000.0
            << 1977275000.0
            << 1979300000.0
            << 1981325000.0
            << 1983350000.0
            << 1985375000.0
            << 1987400000.0
            << 1989425000.0
            << 1991450000.0
            << 1993475000.0
            << 1995500000.0;
    QTest::newRow("case2n9") << settings2 << uint(9) << freq2_9;
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
    freq1_3 << 1015000000.0
            << 1030000000.0
            << 1045000000.0
            << 1060000000.0
            << 1075000000.0
            << 1090000000.0
            << 1105000000.0
            << 1120000000.0
            << 1135000000.0
            << 1150000000.0;
    QTest::newRow("case1n3") << settings1 << uint(3) << freq1_3;

    // n = 5
    QRowVector freq1_5;
    freq1_5 << 1025000000.0
            << 1050000000.0
            << 1075000000.0
            << 1100000000.0
            << 1125000000.0
            << 1150000000.0
            << 1175000000.0
            << 1200000000.0
            << 1225000000.0
            << 1250000000.0;
    QTest::newRow("case1n5") << settings1 << uint(5) << freq1_5;

    // n = 7
    QRowVector freq1_7;
    freq1_7 << 1035000000.0
            << 1070000000.0
            << 1105000000.0
            << 1140000000.0
            << 1175000000.0
            << 1210000000.0
            << 1245000000.0
            << 1280000000.0
            << 1315000000.0
            << 1350000000.0;
    QTest::newRow("case1n7") << settings1 << uint(7) << freq1_7;

    // n = 9
    QRowVector freq1_9;
    freq1_9 << 1045000000.0
            << 1090000000.0
            << 1135000000.0
            << 1180000000.0
            << 1225000000.0
            << 1270000000.0
            << 1315000000.0
            << 1360000000.0
            << 1405000000.0
            << 1450000000.0;
    QTest::newRow("case1n9") << settings1 << uint(9) << freq1_9;

    // Case 2
    IntermodSettings settings2;
    settings2.setCenterFrequency  ( 2, SiPrefix::Giga);
    settings2.setStartToneDistance( 1, SiPrefix::Mega);
    settings2.setStopToneDistance (10, SiPrefix::Mega);
    settings2.setPoints(21);

    // n = 3
    QRowVector freq2_3;
    freq2_3 << 2001500000.0
            << 2002175000.0
            << 2002850000.0
            << 2003525000.0
            << 2004200000.0
            << 2004875000.0
            << 2005550000.0
            << 2006225000.0
            << 2006900000.0
            << 2007575000.0
            << 2008250000.0
            << 2008925000.0
            << 2009600000.0
            << 2010275000.0
            << 2010950000.0
            << 2011625000.0
            << 2012300000.0
            << 2012975000.0
            << 2013650000.0
            << 2014325000.0
            << 2015000000.0;
    QTest::newRow("case2n3") << settings2 << uint(3) << freq2_3;

    // n = 5
    QRowVector freq2_5;
    freq2_5 << 2002500000.0
            << 2003625000.0
            << 2004750000.0
            << 2005875000.0
            << 2007000000.0
            << 2008125000.0
            << 2009250000.0
            << 2010375000.0
            << 2011500000.0
            << 2012625000.0
            << 2013750000.0
            << 2014875000.0
            << 2016000000.0
            << 2017125000.0
            << 2018250000.0
            << 2019375000.0
            << 2020500000.0
            << 2021625000.0
            << 2022750000.0
            << 2023875000.0
            << 2025000000.0;
    QTest::newRow("case2n5") << settings2 << uint(5) << freq2_5;

    // n = 7
    QRowVector freq2_7;
    freq2_7 << 2003500000.0
            << 2005075000.0
            << 2006650000.0
            << 2008225000.0
            << 2009800000.0
            << 2011375000.0
            << 2012950000.0
            << 2014525000.0
            << 2016100000.0
            << 2017675000.0
            << 2019250000.0
            << 2020825000.0
            << 2022400000.0
            << 2023975000.0
            << 2025550000.0
            << 2027125000.0
            << 2028700000.0
            << 2030275000.0
            << 2031850000.0
            << 2033425000.0
            << 2035000000.0;
    QTest::newRow("case2n7") << settings2 << uint(7) << freq2_7;

    // n = 9
    QRowVector freq2_9;
    freq2_9 << 2004500000.0
            << 2006525000.0
            << 2008550000.0
            << 2010575000.0
            << 2012600000.0
            << 2014625000.0
            << 2016650000.0
            << 2018675000.0
            << 2020700000.0
            << 2022725000.0
            << 2024750000.0
            << 2026775000.0
            << 2028800000.0
            << 2030825000.0
            << 2032850000.0
            << 2034875000.0
            << 2036900000.0
            << 2038925000.0
            << 2040950000.0
            << 2042975000.0
            << 2045000000.0;
    QTest::newRow("case2n9") << settings2 << uint(9) << freq2_9;
}
void FrequencyConversionTest::imu() {
    QFETCH(IntermodSettings, settings);
    QFETCH(uint, order);
    QFETCH(QRowVector, freq);

    FrequencyConversionGenerator fg(settings);
    QCOMPARE(fg.upperOutputFreq_Hz(order).size(),  freq.size());
    QCOMPARE(fg.upperOutputFreq_Hz(order).first(), freq.first());
    QCOMPARE(fg.upperOutputFreq_Hz(order).last(),  freq.last());
    QCOMPARE(fg.upperOutputFreq_Hz(order), freq);
}
