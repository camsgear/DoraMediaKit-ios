//
//  CDAMainController.m
//  DORAMediaKit-iOSDemo
//
//  Created by wuping on 21/11/2017.
//  Copyright © 2017 DORAPlayer. All rights reserved.
//

#import "CDAMainController.h"
#import "AppConstant.h"
#import "CDANormalPlayerController.h"
#import "CDASingleH264PlayerController.h"
#import "CDASingleFisheyeController.h"
#import "CDAH265StreamPlayerController.h"
#import "CDADualFisheyeViewController.h"


@interface CDAMainController ()<UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) NSArray *playerStyleArray;

@end

@implementation CDAMainController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"DORAPlayer";
    UITableView *tableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, kScreenWidth, self.view.bounds.size.height) style:UITableViewStylePlain];
    tableView.delegate = self;
    tableView.dataSource = self;
    [self.view addSubview:tableView];
    
    self.playerStyleArray = @[@"视频播放", @"单帧H264播放", @"单鱼眼", @"H265流", @"双鱼眼"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return self.playerStyleArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CellId"];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"CellId"];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    cell.textLabel.text = self.playerStyleArray[indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row == 0) {
        CDANormalPlayerController *npVC = [[CDANormalPlayerController alloc] init];
        [self.navigationController pushViewController:npVC animated:YES];
    }
    else if (indexPath.row == 1) {
        CDASingleH264PlayerController *spVC = [[CDASingleH264PlayerController alloc] init];
        [self.navigationController pushViewController:spVC animated:YES];
    }
    else if (indexPath.row == 2) {
        CDASingleFisheyeController *sfVC = [[CDASingleFisheyeController alloc] init];
        [self.navigationController pushViewController:sfVC animated:YES];
    }
    else if (indexPath.row == 3) {
        CDAH265StreamPlayerController *plVC = [[CDAH265StreamPlayerController alloc] init];
        [self.navigationController pushViewController:plVC animated:YES];
    } else if (indexPath.row == 4) {
        CDADualFisheyeViewController *plVC = [[CDADualFisheyeViewController alloc] init];
        [self.navigationController pushViewController:plVC animated:YES];
    }
}

@end

