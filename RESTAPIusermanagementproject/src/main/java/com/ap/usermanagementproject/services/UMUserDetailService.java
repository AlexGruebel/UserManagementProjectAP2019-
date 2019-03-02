package com.ap.usermanagementproject.services;

import java.util.Set;

import com.ap.usermanagementproject.entities.UserAuthorityEntity;
import com.ap.usermanagementproject.entities.UserDetailEntity;
import com.ap.usermanagementproject.entities.UserPrincipal;
import com.ap.usermanagementproject.entities.UserSecurityEntity;
import com.ap.usermanagementproject.repositories.UserDetailRepository;
import com.ap.usermanagementproject.repositories.UserPermissionRepository;
import com.ap.usermanagementproject.repositories.UserSecurityRepository;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

@Service
public class UMUserDetailService implements UserDetailsService {
 
    
    private UserSecurityRepository userRepository;
    private UserPermissionRepository permissionRepository;
    
 
    @Autowired
    public UMUserDetailService(UserSecurityRepository userRepository, UserPermissionRepository permissionRepository){
        this.userRepository = userRepository;
        this.permissionRepository = permissionRepository;
    }

    @Override
    public UserDetails loadUserByUsername(String username) {
        UserSecurityEntity user = userRepository.findByUserName(username);
        
        Set<UserAuthorityEntity> permissions = permissionRepository.findByUserid(user.getId());
        System.out.println(permissions.size());
        user.setUserPermissions(permissions);
        if (user == null) {
            throw new UsernameNotFoundException(username);
        }
       
        return new UserPrincipal(user);
    }
}