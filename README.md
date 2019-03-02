# UserManagementProjectAP2019-
School project to create an user management system, which supports all CRUD operations. We developed a REST API to serve a C++ QT GUI Application with all the necessary operations to manage users.

The Usermanagement Tool should offer administrators the possibility to edit databases dynamically.
To manage this data there is GUI that displays all the content of a database in a tree view and allows it to be edited.

The GUI communicates with the database via a REST API.
The goal is to access a generic GUI from a concrete database via the REST API.

The concrete database model describes a user administration in which there are users who are in groups and these groups each have certain permissions.

## Used Programminglanguages & Frameworks

* Client C++/QT 5.9.1
* REST API Java 8 /Spring Boot 2.1.3
* Database MySql 5.6 (Sadly we were forced to use this old MySql version, of course we would have taken the latest an greatest if we had a choice)

## Conclusion

The project was an interesting experience. Especially trying out new structures and methods (Backend: Spring Framework => the seemingly endless possibilities
of reflection) was a learning experience.
Unfortunately, the project itself was clearly too ambitious for 2 weeks in the exam phase. There were many ideas left on the track just to ensure the basic functionality.
Despite weekend work and additional work in the afternoon, no dynamic database administration software was created.
We also realized how important a clear project definition is at the beginning of the project.
Despite daily scrum meetings, problems of the dynamic structure were recognized too late. (See Database Metadata, Dynamic Change of Primary Keys)
In the end, however, an interesting piece of software was created in which we learned a lot.

… indeed I (Alex) am planning to take the idea for educational purposes, to create an dynamic application in which user can dynamicly create templates for all kind of CRUD operations, to another project (placeholder).

