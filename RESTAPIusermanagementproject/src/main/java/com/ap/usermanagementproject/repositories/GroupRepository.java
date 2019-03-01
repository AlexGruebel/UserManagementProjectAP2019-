package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.Group;
import org.springframework.data.jpa.repository.JpaRepository;

public interface GroupRepository extends JpaRepository<Group, Integer>{
    
}