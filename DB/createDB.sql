DROP DATABASE IF EXISTS UserManagementProject;

CREATE DATABASE UserManagementProject;

USE UserManagementProject;
/*tables:*/

CREATE TABLE users (
  userID INT PRIMARY KEY auto_increment,
  uuname varchar(255) not null,
  pwhash varchar(8000),
  mail varchar(255)
);

CREATE UNIQUE INDEX users_uuname ON users (uuname);

CREATE TABLE user_groups (
  groupid int primary key auto_increment,
  ugroupname varchar(255) not null,
  description varchar(1000)
);

CREATE UNIQUE INDEX users_ugroupname ON user_groups (ugroupname);

CREATE TABLE user_group_mapping(
  userid int,
  groupid int,
  PRIMARY KEY(userid, groupid)
);

CREATE TABLE permissions (
  permissionid int PRIMARY KEY auto_increment,
  upermissionname varchar(255) unique,
  permission varchar(1000)
);

CREATE TABLE group_permission_mapping (
  groupid int,
  permissionid int,
  PRIMARY KEY (groupid, permissionid)
);

/*default data*/

/*standart groups*/

INSERT INTO user_groups(ugroupname, description)
VALUES('user', 'default group for every user'), ('admin', 'admin group');

/*default user*/

INSERT INTO users(uuname, pwhash)
VALUES('root', 'notImplementedYet')

insert into user_group_mapping
values(1,2),(2,1)