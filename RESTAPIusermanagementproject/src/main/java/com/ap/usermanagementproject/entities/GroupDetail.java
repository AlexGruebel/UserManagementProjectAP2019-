package com.ap.usermanagementproject.entities;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table
public class GroupDetail extends BaseGroup {

    private String description;

    /**
     * @param description the description to set
     */
    public void setDescription(String description) {
        this.description = description;
    }

    /**
     * @return the description
     */
    public String getDescription() {
        return description;
    }
}