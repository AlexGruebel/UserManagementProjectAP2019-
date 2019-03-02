package com.ap.usermanagementproject.entities;

import javax.persistence.Embeddable;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity(name="group")
@Table(name = "user_groups")
@Embeddable
public class GroupEntity extends BaseGroup{}