package com.ap.usermanagementproject.repositories;

import java.util.Set;

import com.ap.usermanagementproject.entities.UserAuthorityEntity;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface UserPermissionRepository extends JpaRepository<UserAuthorityEntity, Integer>{
     
     Set<UserAuthorityEntity> findByUserid(int userid);
}