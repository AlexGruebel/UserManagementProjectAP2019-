package com.ap.usermanagementproject.entities;

public interface IEntity {
    /**
     * updates the attributes on this Entity with the param IEntity if these attributes are not null 
     * @param IEntity 
     * @return this IEntity
     */
    public IEntity merge(IEntity entity);
}