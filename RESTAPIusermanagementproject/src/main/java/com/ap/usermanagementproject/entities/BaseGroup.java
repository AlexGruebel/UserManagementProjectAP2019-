package com.ap.usermanagementproject.entities;

import javax.persistence.Column;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;

@MappedSuperclass
public class BaseGroup {
    
    @Id
    @Column(name="groupid")
    private int id;

    @Column(name="ugroupname")
    private String groupname;

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param groupname the groupname to set
     */
    public void setGroupname(String groupname) {
        this.groupname = groupname;
    }

    /**
     * @return the groupname
     */
    public String getGroupname() {
        return groupname;
    }
}