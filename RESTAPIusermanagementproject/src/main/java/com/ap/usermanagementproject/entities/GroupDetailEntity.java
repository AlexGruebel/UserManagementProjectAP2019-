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
public class GroupDetailEntity extends BaseGroup {

    private String description;

    @ManyToMany        
    @JoinTable(name = "group_permission_mapping"
              ,joinColumns = @JoinColumn(name = "groupid")
              ,inverseJoinColumns = @JoinColumn(name = "permissionid"))
    private Set<PermissionEntity> permissions = new HashSet<PermissionEntity>();

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
    public Set<PermissionEntity> getPermissions() {
        return permissions;
    }

    /**
     * @param permissions the permissions to set
     */
    public void setPermissions(Set<PermissionEntity> permissions) {
        this.permissions = permissions;
    }

    @Override
    public IEntity merge(IEntity entity){
        GroupDetailEntity ngroup =  (GroupDetailEntity) super.merge(entity);

        if(ngroup.getDescription() != null){
            this.setDescription(ngroup.getDescription());
        }
        return this;
    }
}