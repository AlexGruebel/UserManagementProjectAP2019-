package com.ap.usermanagementproject.entities;

import javax.persistence.Entity;
import javax.persistence.Table;

import org.hibernate.annotations.Immutable;

@Entity
@Immutable
@Table(name="users")
public class User extends BaseUser {}