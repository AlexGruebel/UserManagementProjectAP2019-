package com.ap.usermanagementproject.entities;

import java.util.HashSet;
import java.util.Set;

import javax.persistence.Entity;
import javax.persistence.JoinTable;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToMany;
import javax.persistence.Table;

@Entity
@Table(name="user_groups")
public class GroupDetail extends BaseGroup {

    private String description;

    @ManyToMany        
    @JoinTable(name = "group_permission_mapping"
              ,joinColumns = @JoinColumn(name = "groupid")
              ,inverseJoinColumns = @JoinColumn(name = "permissionid"))
    private Set<Permission> permissions = new HashSet<Permission>();

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

    /**
     * @return the permissions
     */
    public Set<Permission> getPermissions() {
        return permissions;
    }

    /**
     * @param permissions the permissions to set
     */
    public void setPermissions(Set<Permission> permissions) {
        this.permissions = permissions;
    }

    @Override
    public IEntity merge(IEntity entity){
        GroupDetail ngroup =  (GroupDetail) super.merge(entity);

        if(ngroup.getDescription() != null){
            this.setDescription(ngroup.getDescription());
        }
        return this;
    }
}