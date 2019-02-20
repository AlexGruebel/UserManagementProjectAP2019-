package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.User;
import org.springframework.data.repository.CrudRepository;

public interface UserRepository extends CrudRepository<User, Integer>{
    
}