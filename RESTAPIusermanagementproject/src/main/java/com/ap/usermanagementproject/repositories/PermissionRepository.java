package com.ap.usermanagementproject.repositories;
import com.ap.usermanagementproject.entities.Permission;
import org.springframework.data.jpa.repository.JpaRepository;

public interface PermissionRepository extends JpaRepository<Permission, Integer> {}