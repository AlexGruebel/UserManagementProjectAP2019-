#ifndef APISINGLETON_H
#define APISINGLETON_H

#include <QObject>
#include <QList>
#include <QPair>
#include <QJsonObject>

#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

class ApiSingleton : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief The loginReply enum
     * This enum contains the return value of a QNetWorkReply status
     */
    enum loginReply
    {
        authenticationError,
        serverError,
        generalError,
        loginUser,
        loginAdmin
    };

    /**
     * @brief getInstance standard scott meyers singleton implementation
     * @return a reference to the object
     */
    static ApiSingleton& getInstance();

    /**
     * @brief login performs a login
     * @param user user who wants to login
     * @param pw password of the user
     * @param url Rest Api server url
     */
    void login(QString user, QString pw, QString url);
    /**
     * @brief userList starts a new userList request to get an updated list of all users
     */
    void userList();
    /**
     * @brief userDetails retrieves a detailed information of a specific user
     * @param id the user id of the specific user
     */
    void userDetails(int id);
    /**
     * @brief sendUserDetails sends an updated userdetails to the rest server to update a specific user
     * @param id the user id of the user to be updated
     * @param doc the json document containing the values for the user
     */
    void sendUserDetails(int id, QJsonDocument doc);

    /**
     * @brief addUser adds a user to the database with the values specified in the json document
     * @param doc values of the user
     */
    void addUser(QJsonDocument doc);
    /**
     * @brief deleteUser deleting a specific user from the database
     * @param id the id of the user to be deleted
     */
    void deleteUser(int id);

private:
    /**
     * @brief ApiSingleton private constructor for the singleton pattern
     */
    ApiSingleton();
    ~ApiSingleton()= default;
    ApiSingleton(const ApiSingleton&)= delete;
    ApiSingleton& operator=(const ApiSingleton&)= delete;

    /**
     * @brief stringToJsonObject a help method to convert a string to a QJsonObject
     * @param s string containg the json information
     * @return valid or invalid QJsonObject
     */
    QJsonObject stringToJsonObject(QString s);

    /**
     * @brief m_restClient network Manager connecting to rest api
     */
    QNetworkAccessManager *m_restClient;

    QString m_user = "";
    QString m_pw = "";
    QString m_url = "";
    /**
     * @brief createPWString help method concatenating a userString and pwString
     * @param user
     * @param pw
     * @return user:pw
     */
    QString createPWString(QString user, QString pw);

signals:
    /**
     * @brief userListReceived asynchron signal that a userList was retrieved
     * @param list the retrieved list
     */
    void userListReceived(QJsonObject list);
    /**
     * @brief userDetailsReceived asynchron signal that new details for a specific user were retrived
     * @param id of the user that has new details
     * @param details of the user
     */
    void userDetailsReceived(int id, QJsonObject details);
    /**
     * @brief loginReceived asynchron signal that a login was tried
     * @param r status of the login (successfull/unsuccessfull, error and login as admin)
     */
    void loginReceived(loginReply r);
};

#endif // APISINGLETON_H
