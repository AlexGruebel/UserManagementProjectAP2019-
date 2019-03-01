package com.ap.usermanagementproject.entities;

import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;

import org.hibernate.annotations.DynamicUpdate;
@MappedSuperclass
@DynamicUpdate
public abstract class BaseUser implements IEntity{

    @Id
    @Column(name="userid")
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    private int id;

    @Column(name="uuname")
    private String userName;

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }
    
    /**
     * @return the userName
     */
    public String getUserName() {
        return userName;
    }

    /**
     * @param userName the userName to set
     */
    public void setUserName(String userName) {
        this.userName = userName;
    }
}