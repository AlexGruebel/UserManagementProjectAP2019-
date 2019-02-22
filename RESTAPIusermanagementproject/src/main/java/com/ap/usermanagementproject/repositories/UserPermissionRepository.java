package com.ap.usermanagementproject.repositories;

import com.ap.usermanagementproject.entities.UserPermission;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

public interface UserPermissionRepository extends JpaRepository<UserPermission, Integer>{
     //Query value becouse I dont found a way to build a "? like column" with the method name
     @Query(value = "select ifnull((select 'true' from user_permissions c where c.user_id= ?1 and ?2 like c.permission limit 1),'false')", nativeQuery=true)
     boolean existsByUserIdAndPermissionLike(int userid, String Permission);
}