
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QEventLoop>
#include <QString>
#include <QStringList>
#include <QTimer>

struct Dummy {
    bool test(const QString& test, const QStringList& args) {
        return true;
    }

    bool process() {
        QEventLoop waitloop;
        QTimer singleshot;
        QObject::connect(&singleshot, &QTimer::timeout, &waitloop, &QEventLoop::quit);
        singleshot.start(1000);
        waitloop.exec();
        return true;
    }
};

TEST(DummyTest, DummyTest)
{
    Dummy tester;
    EXPECT_TRUE(tester.test("Hello", QStringList() << "World"));
    EXPECT_TRUE(tester.process());
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    QTimer::singleShot(0, [&]() {
        ::testing::InitGoogleTest(&argc, argv);
        auto result = RUN_ALL_TESTS();
        app.exit(result);
    });

    return QCoreApplication::exec();
}
